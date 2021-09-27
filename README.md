# Needle_Sift_BOF

## What is this?
Strstr with user-supplied needle and filename as a BOF.

## Why?
Why not? Supply what you want, and don't worry about downloading an entire file that may/may not have what you're looking for.

## How do I run this?
1. In this case, you have two options:
	1. Use the existing, compiled object file, located in the `dist` directory (AKA proceed to major step two)
    2. Compile from source via the `Makefile`
        1. `cd src`
        2. `make clean`
        3. `make`
2. Load the `Aggressor` file, in the `Script Manager`, located in the `dist` directory
3. Within a provided `Beacon`, `beacon> needle_sift PATH_TO_FILE_OF_INTEREST STRING_TO_SEARCH_FOR` (e.g. `needle_sift C:\Users\User\sensitive_file.txt Password`)

## Any known downsides?
- We're still using the `Win32` API and `Dynamic Function Resolution`.  This is for you to determine as far as "risk"
- There's a user-defined cap on what we want the total length of a line to be. (I didn't want to do anything with a heap allocation, and favored some semblance of stability)