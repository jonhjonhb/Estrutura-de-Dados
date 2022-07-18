import string
import random

def RandomStringGenerator():
    print_list = [a for a in string.printable if a not in string.whitespace]

    string_size = random.randrange(1, 11)

    random_list = random.choices(print_list, k=string_size)

    random_string = "".join(random_list)

    return random_string


def RandomMessage(number_words):
    message = ""

    for i in range(number_words - 1):
        message += RandomStringGenerator() + " "

    message += RandomStringGenerator()

    return message


def generateENTREGAS(number_Entregas, arquivo):
    for i in range(number_Entregas):
        User_Number = random.randrange(0, 1000001)

        Message_Number = random.randrange(0, 1000001)

        Word_number = random.randrange(1, 11)

        Output_string = (
            ""
            + "\nENTREGA "
            + str(User_Number)
            + " "
            + str(Message_Number)
            + " "
            + str(Word_number)
            + " "
            + RandomMessage(Word_number)
        )

        arquivo.write(Output_string)


def generateCONSULTAS(number_Consultas, arquivo):
    for i in range(number_Consultas):
        User_Number = random.randrange(0, 1000001)

        Message_Number = random.randrange(0, 1000001)

        Output_string = (
            "" + "\nCONSULTA " + str(User_Number) + " " + str(Message_Number)
        )

        arquivo.write(Output_string)


def generateAPAGAS(number_Apagas, arquivo):
    for i in range(number_Apagas):
        User_Number = random.randrange(0, 1000001)

        Message_Number = random.randrange(0, 1000001)

        Output_string = "" + "\nAPAGA " + str(User_Number) + " " + str(Message_Number)

        arquivo.write(Output_string)

for i in range(5,15):
    Output_file = open("entrada_"+str(i)+".txt", "w")
    Output_file.write(str(random.randrange(1, 50)))
    generateENTREGAS(random.randrange(50, 100), Output_file)
    generateCONSULTAS(random.randrange(50, 100), Output_file)
    generateAPAGAS(random.randrange(1, 100), Output_file)