def caesar_cipher(text, shift):
    encrypted_text = ""
    
    # Iterate through each character in the text
    for char in text:
        # Encrypt uppercase characters
        if char.isupper():
            encrypted_char = chr((ord(char) - ord('A') + shift) % 26 + ord('A'))
            encrypted_text += encrypted_char
        # Encrypt lowercase characters
        elif char.islower():
            encrypted_char = chr((ord(char) - ord('a') + shift) % 26 + ord('a'))
            encrypted_text += encrypted_char
        # Leave any non-alphabetical characters unchanged
        else:
            encrypted_text += char
    
    return encrypted_text

# Example usage:
plaintext = "Hello, World!"
shift = 3
encrypted_text = caesar_cipher(plaintext, shift)
print("Plaintext:", plaintext)
print("Encrypted:", encrypted_text)
