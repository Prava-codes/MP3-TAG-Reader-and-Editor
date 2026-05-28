# 🎵 MP3 Tag Reader and Editor (ID3v2) 

## Description

MP3 Tag Reader and Editor is a CLI-based C project developed to read and edit MP3 metadata using the ID3v2 format. It demonstrates low-level file handling, binary data processing, and metadata manipulation without using external libraries.

## Features

• Read MP3 metadata information
• Edit MP3 metadata tags
• Supports ID3v2 format
• Command-line based interface
• Preserves original audio content during editing

## 👁️ View MP3 Metadata

• View song title

• View artist name

• View album name

• View year information

• View content/genre

• View comments

## ✏️ Edit MP3 Tags

• Edit title (-t)

• Edit artist (-a)

• Edit album (-A)

• Edit year (-y)

• Edit content (-m)

• Edit comments (-c)

## 🛠️ Technologies Used

• C Programming

Concepts Used:

• Structures

• Pointers

• File Handling

• Dynamic Memory Allocation

• String Handling Functions

• Command Line Arguments

• Binary File Operations

• Endianness Conversion

## Project Structure

MP3-Tag-Reader-and-Editor/

├── mp3_main.c
├── mp3_view.c
├── mp3_edit.c
├── functions.c
├── mp3_header.h
└── sample.mp3


## ▶️ Usage

Compile the project:
gcc *.c


👁️ View MP3 metadata:

./a.out -v sample.mp3


✏️ Edit MP3 metadata:

./a.out -e -t "New Title" sample.mp3

./a.out -e -a "Artist Name" sample.mp3

./a.out -e -A "Album Name" sample.mp3

./a.out -e -y "2026" sample.mp3

./a.out -e -m "Melody" sample.mp3

./a.out -e -c "New Comment" sample.mp3

## How It Works

-> Validates command line arguments

-> Checks whether the file is in .mp3 format

-> Verifies ID3 version compatibility

-> Opens the MP3 file in binary mode

-> Reads metadata frames from the file

-> Displays tag information

-> Creates a temporary file during editing

-> Replaces selected tag information

-> Renames the modified file after successful editing


## ✅ Advantages


• User-friendly command line interface

• Reads and edits metadata without affecting audio content

• Supports multiple tag modifications

• Uses temporary files for safer editing

• Efficient binary file handling

## ⚠️ Limitations


• Supports only ID3v2.3 format

• Supports limited metadata fields

• No graphical user interface (GUI)

• Limited error handling for corrupted files

## 📌 Learning Outcomes


• Improved understanding of file handling

• Learned binary file processing

• Gained knowledge of metadata structures

• Practiced dynamic memory allocation

• Improved command-line programming skills

• Understood endianness conversion techniques

## 🎯 Conclusion

This project successfully implements MP3 metadata reading and editing using C programming through a CLI-based approach. It demonstrates practical implementation of low-level file handling, binary data processing, and metadata manipulation without relying on external libraries, while maintaining the integrity of the original MP3 audio content.


#### -PRAVALLIKA THIRUKKOVALLURU
