import random

BYTE = 8 # bits
BYTE_ONES = 255 # 11111111

# Generate random binary key
def generate_key(byte_n):
    return random.getrandbits(byte_n * BYTE)

"""
XOR binary with key. Ex:

     01100100 01101111 01100111 00101110
XOR      ^        ^        ^        ^
     10101010 10101010 10101010 10101010 KEY
         │        │        │        │
         ▼        ▼        ▼        ▼
     11001110 11000101 11001101 10000100
"""
def cipher_xor_ecm(phrase_block, key, BLOCK_BYTES, KEY_BYTES):
    cipher = phrase_block
    for bshift_n in range(max(BLOCK_BYTES//KEY_BYTES, 1)):
        cipher ^= key << BYTE * KEY_BYTES * bshift_n
    return cipher

"""
Get byte at position. Ex:

binary:  01100100 01101111 01100111 00101110
position:   [3]      [2]      [1]      [0]
"""
def byte_at_pos(binary, pos):
    return (binary & (BYTE_ONES << BYTE * pos)) >> BYTE * pos

def apply_cipher(phrase, key, BLOCK_BYTES, KEY_BYTES):

    cipher_text = ""
    block = 0
    for char_idx, char in enumerate(phrase[::-1]):

        """
        transform char block to binary. Ex:

           'd'      'o'      'g'      '.'
            │        │        │        │
            ▼        ▼        ▼        ▼
        01100100 01101111 01100111 00101110
        """
        block |= ord(char) << BYTE * (char_idx % BLOCK_BYTES)

        if (char_idx + 1) % BLOCK_BYTES != 0:
            continue

        cipher_block = cipher_xor_ecm(block, key, BLOCK_BYTES, KEY_BYTES)

        """
        transform binary to char block. Ex:

        11001110 11000101 11001101 10000100
            │        │        │        │
            ▼        ▼        ▼        ▼
            ÿ        Å        Í        ä        
        """
        cipher_text = "".join([chr(byte_at_pos(cipher_block, bshift)) 
                               for bshift in range(BLOCK_BYTES)])[::-1] + cipher_text
        block = 0

    # This is an extra step to when the block isn't complete and the phrase has ran out of chars
    if (char_idx + 1) % BLOCK_BYTES != 0:
        cipher_block = cipher_xor_ecm(block, key, BLOCK_BYTES, KEY_BYTES)
        cipher_text = "".join([chr(byte_at_pos(cipher_block, bshift)) 
                               for bshift in range((char_idx+1) % BLOCK_BYTES)])[::-1] + cipher_text    

    return cipher_text

def main():
    BLOCK_BYTES = 4
    KEY_BYTES = 2

    phrases = [
        "The quick brown fox jumps over the lazy dog.",
        "The five boxing wizards jump quickly.",
        "Pack my box with five dozen liquor jugs."
    ]

    for phrase in phrases:
        
        key = generate_key(KEY_BYTES)
        print("Generated key")
        print(len("Generated key") * "‾")
        print(f"{KEY_BYTES} bytes key: {bin(key)}", end="\n\n")

        encoded_text = apply_cipher(phrase, key, BLOCK_BYTES, KEY_BYTES)
        decoded_text = apply_cipher(encoded_text, key, BLOCK_BYTES, KEY_BYTES)

        print("Original phrase")
        print(len("Original phrase") * "‾")
        print(repr(phrase), end="\n\n")

        print("Encoded text")
        print(len("Encoded text") * "‾")
        print(repr(encoded_text), end="\n\n")

        print("Decoded text")
        print(len("Decoded text") * "‾")
        print(repr(decoded_text), end="\n\n")

if __name__ == '__main__':
    main()