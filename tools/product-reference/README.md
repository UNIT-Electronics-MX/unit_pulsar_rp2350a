# Product Reference build

The UNIT PULSAR RP2350 Product Reference source is maintained in Markdown under
`chapters/`. Document metadata and chapter order are defined in `book.yml`.
Version 0.1.0 is based on the V1.3 schematic, BOM, board artwork, official
RP2350 component datasheet, and technical wiki.

## Local validation build

Requirements:

- Pandoc
- WeasyPrint

Run from the repository root and direct validation output outside the
repository:

```bash
./tools/product-reference/build.sh /tmp/pulsar-product-reference
```

The build produces:

```text
unit_product_reference_v_0_1_0_pulsar_rp2350a.md
unit_product_reference_v_0_1_0_pulsar_rp2350a.docx
unit_product_reference_v_0_1_0_pulsar_rp2350a.html
unit_product_reference_v_0_1_0_pulsar_rp2350a.pdf
```

GitHub Actions publishes the PDF and DOCX under `docs/hardware/`. Do not edit
generated documents or `docs/` manually.

The Markdown chapters are the source of truth. Board values and mappings must
come from controlled source files. Do not infer complete board limits from an
individual component rating. The technical wiki documents intended subsystem
operation and firmware workflows. Values absent from these sources are stated
as unspecified rather than inferred from individual component ratings.

Known source inconsistencies and unspecified board-level values are listed in
Chapter 9.
