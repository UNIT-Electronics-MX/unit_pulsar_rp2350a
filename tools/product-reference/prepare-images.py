#!/usr/bin/env python3
"""Prepare document-sized raster copies without changing hardware originals."""

import argparse
from pathlib import Path
import sys
import warnings

from PIL import Image


# 2400 px covers a 7.2-inch figure at more than 300 dpi.
MAX_DOCUMENT_EDGE = 2400
# The topology exports contain 181 million pixels. Allow these known large
# inputs only in this preprocessing step, with a finite upper bound.
MAX_SOURCE_PIXELS = 200_000_000


def prepare_image(project_dir: Path, output_dir: Path, asset: str) -> None:
    relative_path = Path(asset)
    if relative_path.is_absolute() or ".." in relative_path.parts:
        raise ValueError("image paths must be relative to the repository")
    if relative_path.suffix.lower() not in {".png", ".jpg", ".jpeg"}:
        return

    with Image.open(project_dir / relative_path) as image:
        original_size = image.size
        if max(original_size) <= MAX_DOCUMENT_EDGE:
            image.verify()
            return

        image.thumbnail(
            (MAX_DOCUMENT_EDGE, MAX_DOCUMENT_EDGE),
            Image.Resampling.LANCZOS,
            reducing_gap=3.0,
        )
        destination = output_dir / relative_path
        destination.parent.mkdir(parents=True, exist_ok=True)
        options = {"quality": 95} if image.format == "JPEG" else {}
        image.save(destination, **options)
        print(
            f"Prepared {asset}: {original_size[0]}x{original_size[1]}"
            f" -> {image.width}x{image.height}"
        )


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("project_dir", type=Path)
    parser.add_argument("output_dir", type=Path)
    parser.add_argument("assets", nargs="*")
    args = parser.parse_args()

    Image.MAX_IMAGE_PIXELS = MAX_SOURCE_PIXELS
    warnings.simplefilter("error", Image.DecompressionBombWarning)
    for asset in args.assets:
        try:
            prepare_image(args.project_dir, args.output_dir, asset)
        except (OSError, ValueError, Image.DecompressionBombError,
                Image.DecompressionBombWarning) as error:
            print(f"Error: cannot prepare image {asset}: {error}", file=sys.stderr)
            sys.exit(1)


if __name__ == "__main__":
    main()
