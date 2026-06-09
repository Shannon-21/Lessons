'''
Considere el problema de implementar un programa que permita jugar al ahorcado. 
Tenga en cuenta que se dispone de una colección de palabras posibles (válidas) 
y el programa debe elegir aleatoriamente una palabra de ellas para jugar. 
Se debe permitir el ingreso de caracteres (letras). 
Si la palabra fue adivinada en su totalidad, debe indicarse que se ha ganado el juego. 
En caso contrario, deben mostrarse los caracteres hallados y un guión bajo (”_”) 
en aquellos lugares que todavía no han sido descubiertos. 

Por ejemplo, si la palabra fuera cohete y se hubiera ingresado la letra 'e' 
debería mostrarse: _ _ _ e _ e En caso de que se ingrese un carácter que no 
está presente en la palabra, debe comunicarse el error. 

Luego de 7 intentos fallidos el jugador pierde. No se debe contar como error si 
se ingresa un carácter que no corresponde a una letra del alfabeto o si se 
ingresa un carácter ya ingresado previamente."
'''

import random

words = ("cohete", "ceremonia", "billetera", "estuche", "cenizas", "encefalopatia", "dramatismo", "reformulacion", "ridiculizar")
fail_count = 0
tries = []
current_guess = ""

def input_char(word, guess):
    if len(guess) > 1:
        return 1 if word == guess else -1
    else:
        if guess in tries: 
            print("Already tried the char")
            return 0
        elif guess not in word:
            tries.append(guess)
            global fail_count
            fail_count += 1
            print("tries:", [trie for trie in tries if trie not in word])
            if fail_count == 7: return -1
            return 0
        if guess in word:
            tries.append(guess)
            current_guess = fill_word(word, tries)

        print(current_guess)

        if len(current_guess) == len(word):
            if word == current_guess:
                return 1
            else:
                return 0
            
def fill_word(word, chars):
    out = ""
    for char in word:
        if char in chars:
            out += char
        else:
            out += "_"
    
    return out

if __name__ == '__main__':
    word = random.choice(words)
    current_guess = fill_word(word, tries)
    print(current_guess, " (", len(word), ")")

    guess = ""

    while fail_count < 7:
        guess = input("Your letter or word guess: ")
        exit = False
        
        while not guess.isalpha():
            if guess == "-1":
                exit = True
                break

            guess = input("Must be only alphabet character/s: ")

        if exit:
            print("Loser!")
            break
    
        result = input_char(word, guess)

        if result == 1:
            print("You win!")
            break
        elif result == 0:
            continue
        else:
            print("Loser!")
            print("answer: ", word)
            break

    