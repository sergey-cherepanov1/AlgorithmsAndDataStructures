''' Sergey Cherepanov st129987@student.spbu.ru
   Assignment1
'''

import subprocess
import base64
import pytest

def run_encoder(input_data: str) -> str:
    process = subprocess.run(
        ['./ascii85', '-e'],
        input=input_data.encode('utf-8'),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    if process.returncode != 0:
        pytest.fail(f"Encoder failed with error: {process.stderr.decode()}")
    return process.stdout.decode('utf-8').strip()

@pytest.mark.parametrize("test_input,expected", [
    ("Hello", base64.a85encode(b"Hello").decode('utf-8')),
    ("Test123", base64.a85encode(b"Test123").decode('utf-8')),
    ("", ""),
    ("\x00\x01\x02", base64.a85encode(b"\x00\x01\x02").decode('utf-8')),
])
def test_encoder_with_python_reference(test_input, expected):
    assert run_encoder(test_input) == expected

def run_decoder(input_data: str) -> str:
    """Запускает C++ декодировщик с входными данными"""
    process = subprocess.run(
        ['./ascii85', '-d'],
        input=input_data.encode('utf-8'),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    return process

@pytest.mark.parametrize("test_input,expected", [
    (base64.a85encode(b"Hello").decode('utf-8'), "Hello"),
    (base64.a85encode(b"Test123").decode('utf-8'), "Test123"),
    ("z", "\x00\x00\x00\x00"),
    ("", ""),
])
def test_decoder_with_python_reference(test_input, expected):
    result = run_decoder(test_input)
    assert result.returncode == 0
    assert result.stdout.decode('utf-8').strip() == expected

@pytest.mark.parametrize("invalid_input", [
    "7",
    "87cUR!",
    "87czURD",
    "abcde\x00",
])
def test_decoder_invalid_data(invalid_input):
    result = run_decoder(invalid_input)
    assert result.returncode != 0
    assert "Error" in result.stderr.decode('utf-8')
