### ASCII85 Encoder/Decoder

#### Overview
Interactive command-line tool for encoding/decoding text and binary data using ASCII85 format.

#### Build
make

#### Usage Modes

1. **Interactive Mode** (default):

# Encoding
./ascii85
Hello
87cURD
[Ctrl+D to exit]

# Decoding 
./ascii85 -d
87cURD
Hello
[Ctrl+D to exit]

2. **Single-command Mode**:

# Encode one string
echo "Hello" | ./ascii85

# Decode one string
echo "87cURD" | ./ascii85 -d

3. **File Processing**:

# Encode file
./ascii85 < input.txt > encoded.txt

# Decode file
./ascii85 -d < encoded.txt > output.txt
