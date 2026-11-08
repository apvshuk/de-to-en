import xml.etree.ElementTree as ET
import re

INPUT_FILE = "dewiktionary-latest-pages-articles.xml"
OUTPUT_FILE = "german_english.tsv"

NS = "{http://www.mediawiki.org/xml/export-0.11/}"

def extract_english(text):
    # Find the Übersetzungen (translations) section
    trans_start = text.find("{{Übersetzungen}}")
    if trans_start == -1:
        return None
    
    trans_section = text[trans_start:]
    
    # Find all {{Ü|en|word}} patterns
    matches = re.findall(r'\{\{Ü\|en\|([^}|]+)', trans_section)
    
    if not matches:
        return None
    
    # Join multiple translations with a comma
    return ", ".join(matches)

count = 0

with open(INPUT_FILE, "r", encoding="utf-8") as infile, \
     open(OUTPUT_FILE, "w", encoding="utf-8") as outfile:

    context = ET.iterparse(infile, events=("end",))

    title = None

    for event, elem in context:
        tag = elem.tag

        if tag == f"{NS}title":
            title = elem.text

        elif tag == f"{NS}text":
            text = elem.text or ""

            if title and "{{Sprache|Deutsch}}" in text:
                english = extract_english(text)
                if english:
                    outfile.write(f"{title}\t{english}\n")
                    count += 1

        # Free memory — critical for large files
        elem.clear()

print(f"Done. {count} entries written to {OUTPUT_FILE}")
