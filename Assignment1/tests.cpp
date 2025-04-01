/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment1
*/

#include "Ascii85.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(Ascii85Test, EncodeEmptyInput) {
    Ascii85 encoder;
    std::vector<uint8_t> empty;
    EXPECT_EQ(encoder.encode(empty), "");
}

TEST(Ascii85Test, EncodeSingleCharacter) {
    Ascii85 encoder;
    std::vector<uint8_t> input = {'A'};
    EXPECT_EQ(encoder.encode(input), "5l");
}

TEST(Ascii85Test, EncodeFourCharacters) {
    Ascii85 encoder;
    std::vector<uint8_t> input = {'T', 'e', 's', 't'};
    EXPECT_EQ(encoder.encode(input), "<+U,m");
}

TEST(Ascii85Test, EncodeFourZeroBytes) {
    Ascii85 encoder;
    std::vector<uint8_t> input = {0, 0, 0, 0};
    EXPECT_EQ(encoder.encode(input), "z");
}

TEST(Ascii85Test, EncodeStreamWithPadding) {
    Ascii85 encoder;
    std::string input = "Hello";
    std::istringstream in(input);
    std::ostringstream out;
    encoder.encodeStream(in, out);
    EXPECT_EQ(out.str(), "87cURDZ");
}

TEST(Ascii85Test, DecodeEmptyInput) {
    Ascii85 encoder;
    std::string empty;
    auto result = encoder.decode(empty);
    EXPECT_TRUE(result.empty());
}

TEST(Ascii85Test, DecodeSingleGroup) {
    Ascii85 encoder;
    std::string input = "87cURDZ";
    auto result = encoder.decode(input);
    std::string output(result.begin(), result.end());
    EXPECT_EQ(output, "Hello");
}

TEST(Ascii85Test, DecodeZForFourZeroBytes) {
    Ascii85 encoder;
    std::string input = "z";
    auto result = encoder.decode(input);
    EXPECT_EQ(result, std::vector<uint8_t>({0, 0, 0, 0}));
}

TEST(Ascii85Test, DecodeStreamWithPadding) {
    Ascii85 encoder;
    std::string input = "87cURDZ";
    std::istringstream in(input);
    std::ostringstream out;
    encoder.decodeStream(in, out);
    EXPECT_EQ(out.str(), "Hello");
}

TEST(Ascii85Test, DecodeInvalidCharacterThrows) {
    Ascii85 encoder;
    std::string input = "87cUR!";
    std::istringstream in(input);
    std::ostringstream out;
    EXPECT_THROW(encoder.decodeStream(in, out), std::runtime_error);
}

TEST(Ascii85Test, DecodeIncompleteFinalGroupThrows) {
    Ascii85 encoder;
    std::string input = "7";
    std::istringstream in(input);
    std::ostringstream out;
    EXPECT_THROW(encoder.decodeStream(in, out), std::runtime_error);
}

TEST(Ascii85Test, DecodeZInMiddleOfGroupThrows) {
    Ascii85 encoder;
    std::string input = "87czURD";
    std::istringstream in(input);
    std::ostringstream out;
    EXPECT_THROW(encoder.decodeStream(in, out), std::runtime_error);
}

TEST(Ascii85Test, RoundTripEncodingDecoding) {
    Ascii85 encoder;
    std::string original = "This is a test string for ASCII85 encoding/decoding!";
    std::vector<uint8_t> original_data(original.begin(), original.end());
    
    std::string encoded = encoder.encode(original_data);
    auto decoded_data = encoder.decode(encoded);
    std::string decoded(decoded_data.begin(), decoded_data.end());
    
    EXPECT_EQ(decoded, original);
}

TEST(Ascii85Test, RoundTripWithSpecialCharacters) {
    Ascii85 encoder;
    std::string original = "Special chars: \n\t\r\x00\xFF";
    std::vector<uint8_t> original_data(original.begin(), original.end());
    
    std::string encoded = encoder.encode(original_data);
    auto decoded_data = encoder.decode(encoded);
    std::string decoded(decoded_data.begin(), decoded_data.end());
    
    EXPECT_EQ(decoded, original);
}
