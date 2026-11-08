# detoeng

A command-line German to English dictionary tool for Linux, written in C.

## Overview

`detoeng` is a fast, offline German-to-English word translator that runs entirely from the terminal. It is built in C and uses a binary search algorithm to look up words from a dictionary of over 80,000 entries extracted from the German Wiktionary dump.

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
git clone https://github.com/apvshuk/detoeng
cd detoeng
```

### 2. Compile the binary

```bash
gcc -o detoeng main.c
```

### 3. Install the binary system-wide

```bash
sudo cp detoeng /usr/local/bin/detoeng
```

### 4. Install the dictionary

```bash
sudo mkdir -p /usr/share/detoeng
sudo cp german_english.tsv /usr/share/detoeng/
```

`detoeng` is now available globally from any directory.

## Usage

```bash
detoeng <german_word>
```

### Examples

```bash
detoeng Hund
# dog

detoeng Katze
# cat

detoeng Haus
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

1. On startup, `detoeng` loads the entire TSV dictionary into an array of structs in memory.
2. The array is sorted alphabetically using `qsort`.
3. The query word is looked up using `bsearch` — a standard library binary search implementation.
4. The result is printed to stdout.

## Uninstallation

```bash
sudo rm /usr/local/bin/detoeng
sudo rm -rf /usr/share/detoeng
```

## License

The source code is released under the MIT License.

The dictionary data is derived from the German Wiktionary, which is licensed under the [Creative Commons Attribution-ShareAlike 3.0 Unported License](https://creativecommons.org/licenses/by-sa/3.0/).

## Author

[apvshuk](https://github.com/apvshuk)
