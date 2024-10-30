// Given an UTF-8 string, return the index of the first invalid byte.
// If there are no invalid bytes, return -1.

// Do NOT change this function's return type or signature.
int invalid_utf8_byte(char *utf8_string) {
    
    // TODO: implement this function
    unsigned char *s = (unsigned char *)utf8_string;
    int i = 0;

    while (s[i]) {
        if (s[i] <= 0x7F) {
            // 1-byte character (ASCII)
            i++;
        } else if (s[i] >= 0xC2 && s[i] <= 0xDF) {
            // 2-byte character
            if (s[i+1] >= 0x80 && s[i+1] <= 0xBF) {
                i += 2;
            } else {
                return i + 1;
            }
        } else if (s[i] >= 0xE0 && s[i] <= 0xEF) {
            // 3-byte character
            if (s[i] == 0xE0) {
                if (s[i+1] >= 0xA0 && s[i+1] <= 0xBF && s[i+2] >= 0x80 && s[i+2] <= 0xBF) {
                    i += 3;
                } else {
                    return (s[i+1] < 0xA0 || s[i+1] > 0xBF) ? i + 1 : i + 2;
                }
            } else if (s[i] == 0xED) {
                if (s[i+1] >= 0x80 && s[i+1] <= 0x9F && s[i+2] >= 0x80 && s[i+2] <= 0xBF) {
                    i += 3;
                } else {
                    return (s[i+1] < 0x80 || s[i+1] > 0x9F) ? i + 1 : i + 2;
                }
            } else {
                if (s[i+1] >= 0x80 && s[i+1] <= 0xBF && s[i+2] >= 0x80 && s[i+2] <= 0xBF) {
                    i += 3;
                } else {
                    return (s[i+1] < 0x80 || s[i+1] > 0xBF) ? i + 1 : i + 2;
                }
            }
        } else if (s[i] >= 0xF0 && s[i] <= 0xF4) {
            // 4-byte character
            if (s[i] == 0xF0) {
                if (s[i+1] >= 0x90 && s[i+1] <= 0xBF && s[i+2] >= 0x80 && s[i+2] <= 0xBF && s[i+3] >= 0x80 && s[i+3] <= 0xBF) {
                    i += 4;
                } else {
                    if (s[i+1] < 0x90 || s[i+1] > 0xBF) return i + 1;
                    if (s[i+2] < 0x80 || s[i+2] > 0xBF) return i + 2;
                    return i + 3;
                }
            } else if (s[i] == 0xF4) {
                if (s[i+1] >= 0x80 && s[i+1] <= 0x8F && s[i+2] >= 0x80 && s[i+2] <= 0xBF && s[i+3] >= 0x80 && s[i+3] <= 0xBF) {
                    i += 4;
                } else {
                    if (s[i+1] < 0x80 || s[i+1] > 0x8F) return i + 1;
                    if (s[i+2] < 0x80 || s[i+2] > 0xBF) return i + 2;
                    return i + 3;
                }
            } else {
                if (s[i+1] >= 0x80 && s[i+1] <= 0xBF && s[i+2] >= 0x80 && s[i+2] <= 0xBF && s[i+3] >= 0x80 && s[i+3] <= 0xBF) {
                    i += 4;
                } else {
                    if (s[i+1] < 0x80 || s[i+1] > 0xBF) return i + 1;
                    if (s[i+2] < 0x80 || s[i+2] > 0xBF) return i + 2;
                    return i + 3;
                }
            }
        } else {
            // Invalid first byte
            return i;
        }
    }

    
    return -1;
}
