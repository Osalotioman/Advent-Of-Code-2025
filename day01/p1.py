"""Manim visualization for Advent of Code 2025 Day 1, part 1.

The animation shows how the pointer moves around a 100-slot circular track
and highlights each visit to the zero position. Change the constants below to
adjust the preview speed, radius, or pointer color without touching the core logic.
"""

from __future__ import annotations

from dataclasses import dataclass
from math import pi
from pathlib import Path
from typing import Iterable

import numpy as np
from manim import (
    BLUE_E,
    BLACK,
    Circle,
    DL,
    Dot,
    DOWN,
    FadeIn,
    Flash,
    GREY,
    LEFT,
    Line,
    Scene,
    TAU,
    Text,
    Transform,
    UL,
    UR,
    UP,
    VGroup,
    ValueTracker,
    WHITE,
    always_redraw,
    linear,
    Tex,
)

INPUT_PATH = Path(__file__).with_name("i")
RADIUS = 3.8  # Radius of the circular track; increase to add breathing room.
START_POS = 50  # Starting slot (default from AoC description).
PREVIEW_LIMIT = 60  # Number of instructions to animate before showing summary.
POINTER_COLOR = BLUE_E  # Pick any Manim color here if the default is hard to see.
ZERO_MARKER_COLOR = "#d7d7d7"
ZERO_HIT_FLASH_COLOR = "#52c7ff"


@dataclass(frozen=True)
class MovementEvent:
    instruction: str
    start_pos: int
    end_pos: int
    zero_hit: bool
    steps: int
    direction: str


def parse_instructions(path: Path) -> list[str]:
    """Read the raw input file and return clean instructions.

    Expects lines like "R27" or "L10". Blank or malformed lines are skipped.
    """
    raw = path.read_text().splitlines()
    return [line.strip() for line in raw if line.strip()]


def compute_events(instructions: Iterable[str], start_pos: int = START_POS) -> tuple[list[MovementEvent], int]:
    """Convert raw instructions into detail-rich events for animation.

    The list includes start/end positions, direction, step count, and whether zero
    was reached. We also count how often zero was hit for the final summary.
    """
    events: list[MovementEvent] = []
    current = start_pos
    zero_hits = 0
    for instruction in instructions:
        direction = instruction[0]
        steps = int(instruction[1:])
        delta = steps if direction == "R" else -steps
        next_pos = (current + delta) % 100
        zero_hit = next_pos == 0
        if zero_hit:
            zero_hits += 1
        events.append(
            MovementEvent(
                instruction=instruction,
                start_pos=current,
                end_pos=next_pos,
                zero_hit=zero_hit,
                steps=steps,
                direction=direction,
            )
        )
        current = next_pos
    return events, zero_hits


def position_to_angle(position: int) -> float:
    return TAU * (position / 100) - pi / 2


def point_from_angle(angle: float) -> np.ndarray:
    # Use np.multiply so type checkers understand we're scaling the vector.
    base = np.array([np.cos(angle), np.sin(angle), 0.0], dtype=float)
    return np.multiply(base, RADIUS)


class CircularTrackPreview(Scene):
    def construct(self) -> None:
        instructions = parse_instructions(INPUT_PATH)
        events, total_zero_hits = compute_events(instructions)
        preview_events = events[:PREVIEW_LIMIT]

        title = Text("Advent of Code 2025 – Day 1 (Part 1)").scale(0.6).to_edge(UP)
        subtitle = Text("Pointer wraps around a circular track of 100 positions", font_size=24).next_to(title, DOWN)

        # Track, zero marker, and ticks build the physical reference frame for movement.
        track = Circle(radius=RADIUS, color=GREY)
        zero_marker = Dot(point_from_angle(position_to_angle(0)), color=ZERO_MARKER_COLOR, radius=0.12)
        ticks = self._build_ticks()

        angle_tracker = ValueTracker(0)
        angle_tracker.set_value(position_to_angle(START_POS))
        pointer = Dot(color=POINTER_COLOR).add_updater(
            lambda mob: mob.move_to(point_from_angle(angle_tracker.get_value()))
        )

        # Counter label follows the zero hits so viewers can see the running total.
        counter_tracker = ValueTracker(0)
        counter_label = always_redraw(
            lambda: Tex(
                f"Zero hits: {int(counter_tracker.get_value())}",
                font_size=28,
            ).to_corner(UR)
        )
        instruction_text = Text("Preparing preview...", font_size=24).scale(0.85)
        instruction_text.add_background_rectangle(color=BLACK, opacity=0.55, buff=0.15)
        instruction_text.next_to(title, DOWN, buff=0.2).to_edge(LEFT, buff=0.2)

        # Add the static elements once; the pointer is updated every frame.
        self.add(track, ticks, zero_marker, pointer, title, subtitle, counter_label, instruction_text)

        running_zero_hits = 0
        for index, event in enumerate(preview_events, start=1):
            new_instruction = Text(f"Move {index}: {event.instruction}", font_size=24).scale(0.85)
            new_instruction.add_background_rectangle(color=BLACK, opacity=0.55, buff=0.15)
            new_instruction.next_to(title, DOWN, buff=0.2).to_edge(LEFT, buff=0.2)
            self.play(Transform(instruction_text, new_instruction), run_time=0.2)

            rotation_delta = (
                -event.steps * TAU / 100
                if event.direction == "R"
                else event.steps * TAU / 100
            )
            start_angle = angle_tracker.get_value()
            target_angle = start_angle + rotation_delta
            # Slow down the animation so viewers can follow the steps. Adjust run_time here
            # if you want faster/slower motion (event.steps scales with step count).
            self.play(
                angle_tracker.animate.set_value(target_angle),
                run_time=min(2.0, max(0.7, event.steps * 0.01)),
                rate_func=linear,
            )

            if event.zero_hit:
                running_zero_hits += 1
                self.play(
                    counter_tracker.animate.set_value(running_zero_hits),
                    Flash(point_from_angle(position_to_angle(0)), color=ZERO_HIT_FLASH_COLOR, flash_radius=0.8, time_width=0.15),
                )
            else:
                counter_tracker.set_value(running_zero_hits)

        summary = VGroup(
            Text("Full input summary", font_size=28),
            Tex(f"Total instructions: {len(events)}", font_size=24),
            Tex(f"Total zero hits: {total_zero_hits}", font_size=24),
            Tex(f"Previewed: {len(preview_events)} moves", font_size=24),
        ).arrange(DOWN, aligned_edge=LEFT)
        summary.to_corner(DL, buff=0.5)
        summary.shift(np.multiply(LEFT, 0.2))
        # Summary fades in after the preview to avoid covering the track during animation.
        self.play(FadeIn(summary))

    def _build_ticks(self) -> VGroup:
        ticks = VGroup()
        # Draw ticks every five slots, labeling multiples of ten.
        for position in range(0, 100, 5):
            angle = position_to_angle(position)
            outer = point_from_angle(angle)
            inner = np.multiply(outer, 0.9)
            ticks.add(Line(inner, outer, stroke_width=2, color=WHITE))
            if position % 10 == 0:
                label = Text(str(position), font_size=20)
                label.move_to(np.multiply(outer, 1.4))
                ticks.add(label)
        return ticks


if __name__ == "__main__":
    events, total = compute_events(parse_instructions(INPUT_PATH))
    print(f"Instructions parsed: {len(events)}")
    print(f"Total zero hits: {total}")# Visualization of aoc problem 1, part 1 with manim