import string

def preprocess_text(text):
    text = text.replace(" ", "").upper()
    text = text.replace("J", "I")
    pairs = []
    i = 0
    while i < len(text):
        if i == len(text) - 1 or text[i] == text[i + 1]:
            pairs.append(text[i] + 'X')
            i += 1
        else:
            pairs.append(text[i] + text[i + 1])
            i += 2
    return pairs

def create_playfair_matrix(key):
    key = key.replace(" ", "").upper()
    key = "".join(dict.fromkeys(key))
    
    alphabet = string.ascii_uppercase.replace("J", "")
    matrix = list(key)
    
    for char in alphabet:
        if char not in matrix:
            matrix.append(char)
    
    playfair_matrix = [matrix[i:i+5] for i in range(0, 25, 5)]
    
    return playfair_matrix

def find_position(matrix, letter):
    for i in range(5):
        for j in range(5):
            if matrix[i][j] == letter:
                return i, j
    return None, None

def playfair_cipher(plaintext, key):
    pairs = preprocess_text(plaintext)
    matrix = create_playfair_matrix(key)
    
    encrypted_text = ""
    
    for pair in pairs:
        r1, c1 = find_position(matrix, pair[0])
        r2, c2 = find_position(matrix, pair[1])
        
        if r1 == r2:
            encrypted_pair = matrix[r1][(c1 + 1) % 5] + matrix[r2][(c2 + 1) % 5]
        elif c1 == c2:
            encrypted_pair = matrix[(r1 + 1) % 5][c1] + matrix[(r2 + 1) % 5][c2]
        else:
            encrypted_pair = matrix[r1][c2] + matrix[r2][c1]
        
        encrypted_text += encrypted_pair
    
    return encrypted_text

# Example usage:
plaintext = "Hello World"
key = "PLAYFAIREXAMPLE"
encrypted_text = playfair_cipher(plaintext, key)
print("Plaintext:", plaintext)
print("Key:", key)
print("Encrypted:", encrypted_text)
