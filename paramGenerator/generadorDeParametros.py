def convert_to_hex_array_little_endian(number_str, array_name):
    # Convert the number to hexadecimal
    hex_str = hex(int(number_str))[2:]  # Remove '0x' prefix
    # Ensure the hex string is a multiple of 16 characters
    hex_str = hex_str.zfill((len(hex_str) + 15) // 16 * 16)
    # Split the hex string into 16-character chunks
    hex_chunks = [hex_str[i:i+16] for i in range(0, len(hex_str), 16)]
    
    # Convert each chunk to little endian format
    little_endian_chunks = []
    for chunk in hex_chunks:
        little_endian_chunk = ''.join(reversed([chunk[i:i+2] for i in range(0, len(chunk), 2)]))
        little_endian_chunks.append(f'0x{little_endian_chunk}')
    
    # Fill with zeros if necessary to reach 20 elements
    while len(little_endian_chunks) < 20:
        little_endian_chunks.append('0x0000000000000000')
    
    # Format the output as an array
    formatted_array = f"uint64_t {array_name}[20] = {{"
    formatted_array += ", ".join(little_endian_chunks)
    formatted_array += "};"
    
    return formatted_array

# Input values
g = "6695856225803740124120548153445732538245829809300010853545039340997056603694"
p = "7918324333004779287780879909121159911537551977796076554305607309994905870203"
x = "7088837878395279488160260190894349689792878066363954964494976508638671882349"

m = "352015466596088420260883280075658662319625787846437566"

# Convert and print the formatted arrays
print(convert_to_hex_array_little_endian(g, "g"))
print(convert_to_hex_array_little_endian(p, "p"))
print(convert_to_hex_array_little_endian(x, "x"))
print(convert_to_hex_array_little_endian(m, "m"))
