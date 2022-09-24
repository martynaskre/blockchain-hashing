# VU Blockchain hashing algorithm

## Idea

General idea for this hashing algorithm revolves around using `XOR` and `bit rotations`.

```
ABC <- "ABCDEF"

Function makeHash(string str)
    characterSum <- 0
    output <- ''

    For i = 0 To Len(str)
        character <- str[i]
        
        characterSum += character Xor rotateRight(character, character)
    Endfor
    
    characterSumArray <- INT_TO_STRING(characterSum)
    
    For i = 0 To 64
        charIndex <- characterSumArray[i] * i
        
        output[i] = ABC[charIndex]
    Endfor
    
    Return output
Endfunction        
```