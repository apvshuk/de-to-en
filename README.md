# detoen

A command-line German to English dictionary tool for Linux, written in C.

## Overview

`detoen` is a fast, offline German-to-English word translator that runs entirely from the terminal. It is built in C and uses a binary search algorithm to look up words from a dictionary of over 80,000 entries extracted from the German Wiktionary dump.

## Features

- Over 80,000 German-English dictionary entries sourced from the German Wiktionary
- Fast binary search lookup
- Fully offline — no internet connection required after installation
- Lightweight single binary with no runtime dependencies

## Requirements

- Linux
- GCC
- Python 3 (only if regenerating the dictionary)

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/apvshuk/detoen
cd detoen
```

### 2. Compile the binary

```bash
gcc -o detoen main.c
```

### 3. Install the binary system-wide

```bash
sudo cp detoen /usr/local/bin/detoen
```

### 4. Install the dictionary

```bash
sudo mkdir -p /usr/share/detoen
sudo cp german_english.tsv /usr/share/detoen/
```

`detoen` is now available globally from any directory.

## Usage

```bash
detoen <german_word>
```

### Examples

```bash
detoen Hund
# dog

detoen Katze
# cat

detoen Haus
# house
```

## Dictionary

The dictionary file `german_english.tsv` was generated from the German Wiktionary XML dump (`dewiktionary-latest-pages-articles.xml.bz2`), available at:

```
https://dumps.wikimedia.org/dewiktionary/latest/
```

The included Python script `parse.py` was used to extract German-English translation pairs from the raw XML and produce the TSV file. Each line in the TSV follows this format:

```
GermanWord<TAB>English translation, alternate translation
```

To regenerate the dictionary from a fresh Wiktionary dump:

```bash
python3 parse.py
```

This will produce a new `german_english.tsv` in the current directory.

## How It Works

> **Note:** The dictionary path is hardcoded in `main.c`. Make sure this line reflects the correct path before compiling:
> ```c
> fopen("/usr/share/detoen/german_english.tsv", "r");
> ```

1. On startup, `detoen` loads the entire TSV dictionary into an array of structs in memory.
2. The array is sorted alphabetically using `qsort`.
3. The query word is looked up using `bsearch` — a standard library binary search implementation.
4. The result is printed to stdout.

## Uninstallation

```bash
sudo rm /usr/local/bin/detoen
sudo rm -rf /usr/share/detoen
```

## License

The source code is released under the MIT License.

The dictionary data is derived from the German Wiktionary, which is licensed under the [Creative Commons Attribution-ShareAlike 3.0 Unported License](https://creativecommons.org/licenses/by-sa/3.0/).

## Author

[apvshuk](https://github.com/apvshuk)
