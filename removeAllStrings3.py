import re
import os

def find_string_in_binary(binary_data, string_literal):
    byte_sequence = bytes(string_literal.encode('utf-8').decode('unicode_escape'), 'utf-8')
    offset = binary_data.find(byte_sequence)
    return offset

def is_within_comment(line, string_start_index):
    comment_start = line.find('/*')
    comment_end = line.find('*/', comment_start + 2)
    if comment_start != -1 and comment_end != -1:
        return comment_start < string_start_index < comment_end
    comment_start = line.find('//')
    if comment_start != -1:
        return string_start_index > comment_start
    return False

def is_already_replaced(line, match):
    # Check if the string is already replaced with a reference to the binary file
    return '&AVATAR[' in line[:match.start()]

with open('C:\\Users\\Jim\\AppData\\LocalLow\\SwivelChairGames\\ANKH-VR\\u4\\AVATAR.EXE', 'rb') as bin_file:
    binary_data = bin_file.read()

source_directory = 'S:\\u4-decompiled\\SRC\\'
string_regex = r'"(\\.|[^"\\])*"'

for filename in os.listdir(source_directory):
    if filename.endswith('.C') or filename.endswith('.c'):
        file_path = os.path.join(source_directory, filename)
        with open(file_path, 'r') as file:
            source_code = file.readlines()

        new_source_code = []
        for line in source_code:
            matches = re.finditer(string_regex, line)
            for match in matches:
                string_literal = match.group(0)  # Include the quotes for exact matching
                if string_literal != '""' and not is_within_comment(line, match.start()) and not is_already_replaced(line, match):
                    offset = find_string_in_binary(binary_data, string_literal[1:-1])
                    if offset >= 0:
                        hex_offset = f'0x{offset:X}'
                        line = line.replace(string_literal, f'&AVATAR[{hex_offset}] /* {string_literal} */')
            new_source_code.append(line)

        with open(file_path, 'w') as file:
            file.writelines(new_source_code)
