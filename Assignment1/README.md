```markdown
# ASCII85 Encoder/Decoder

## Overview
Interactive command-line tool for encoding/decoding text and binary data using ASCII85 format.

## Build
```bash
make
```

## Usage Modes

### 1. Interactive Mode (default)

#### Encoding
```bash
./ascii85
Hello
87cURD
[Ctrl+D to exit]
```

#### Decoding
```bash
./ascii85 -d
87cURD
Hello
[Ctrl+D to exit]
```

### 2. Single-command Mode

#### Encode one string
```bash
echo "Hello" | ./ascii85
```

#### Decode one string
```bash
echo "87cURD" | ./ascii85 -d
```

### 3. File Processing

#### Encode file
```bash
./ascii85 < input.txt > encoded.txt
```

#### Decode file
```bash
./ascii85 -d < encoded.txt > output.txt
```
