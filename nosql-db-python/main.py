"""
REQUIREMENTS:

MESSAGE STRUCTURE
1. Request Messages
A Request Message consists of a command, a key, a value, and a value type.
The last three are optional depending on the message.
A ; = a delimiter. There must always be three ; characters in the message,
even if some optional fields are not included.

COMMAND;[KEY];[VALUE];[VALUE TYPE]

COMMAND is a command from the list above
KEY is a string to be used as a data store key (optional)
VALUE is a integer, list, or string to be stored in the data store (optional)
Lists are represented as a comma-separated series of strings: "red,green,blue"
VALUE TYPE describes what type VALUE should be interpreted as
Possible values: INT, STRING, LIST

Examples
"PUT;foo;1;INT"
"GET;foo;;"
"PUTLIST;bar;a,b,c;LIST"
"APPEND;bar;d;STRING
"GETLIST;bar;;"

2. Response Messages
A Response Message consists of two parts, separated by a ;. 
First part is always True|False based on whether the command was successful.
Second part is the command message. On errors, this will describe the error.
On successful commands that don't expect a value to be returned (like PUT),
this will be a success message. 
For commands that expect a value to be returned (GET) = the value itself.

Examples
"True;Key [foo] set to [1]"
"True;Key [bar] set to [['a', 'b', 'c']]"
"True;{'PUTLIST': {'success': 1, 'error': 0}, 'STATS': {'success': 0, 'error': 0}, 
'INCREMENT': {'success': 0, 'error': 0}, 'GET': {'success': 0, 'error': 0}, 
'PUT': {'success': 0, 'error': 0}, 'GETLIST': {'success': 1, 'error': 0}, 
'APPEND': {'success': 1, 'error': 0}, 'DELETE': {'success': 0, 'error': 0
"""


import socket

HOST = 'localhost'
PORT = 50505
SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

STATS = {
    'PUT': {'success': 0, 'error': 0},
    'GET': {'success': 0, 'error': 0},
    'GETLIST': {'success': 0, 'error': 0},
    'PUTLIST': {'success': 0, 'error': 0},
    'INCREMENT': {'success': 0, 'error': 0},
    'APPEND': {'success': 0, 'error': 0},
    'DELETE': {'success': 0, 'error': 0},
    'STATS': {'success': 0, 'error': 0}
}

COMMAND_HANDLERS = {
    'PUT': handle_put,
    'GET': handle_get,
    'GETLIST': handle_getlist,
    'PUTLIST': handle_putlist,
    'INCREMENT': handle_increment,
    'APPEND': handle_append,
    'DELETE': handle_delete,
    'STATS': handle_stats
}

DATA = {}


def main():
    # Main entry point for the code.

    SOCKET.bind((HOST, PORT))
    SOCKET.listen(1)

    while 1:
        connection, address = SOCKET.accept()
        print('New connection from [{}]'.format(address))
        data = connection.recv(4096).decode()
        command, key, value = parse_message(data)

        if command == 'STATS':
            response = handle_stats()
        elif command in ('GET', 'GETLIST', 'INCREMENT', 'DELETE'):
            response = COMMAND_HANDLERS[command](key)
        elif command in ('PUT', 'PUTLIST', 'APPEND'):
            response = COMMAND_HANDLERS[command](key, value)
        else:
            response = (False, 'Unknown command type [{}]'.format(command))

    update_stats(command, response[0])
    connection.sendall('{};{}'.format(response[0], response[1]))
    connection.close()


if __name__ == '__main__':
    main()


# COMMAND PARSER

def parse_message(data):

    # Return a tuple containing the command, the key, and
    # (optionally) the value cast to the appropriate type.

    command, key, value, value_type = data.strip().split(';')
    if value_type:
        if value_type == 'LIST':
            value = value.split(',')
        elif value_type == 'INT':
            value = int(value)
        else:
            value = str(value)
    else:
        value = None

    return command, key, value


# COMMAND HANDLERS

def handle_stats(command, success):
    # Update the STATS dict with info if executing
    # *command* was a *success*.
    if success:
        STATS[command]['success'] += 1
    else:
        STATS[command]['error'] += 1


def handle_put(key, value):
    # Return a tuple containing True and the message
    # to send back to the client.
    DATA[key] = value
    return (True, 'Key [{}] set to [{}]'.format(key, value))


def handle_get(key):
    # Return a tuple containing True if key exists and the message
    # to send back to the client.
    if key not in DATA:
        return (False, 'Error: Key [{}] not found'.format(key))
    else:
        return (True, DATA[key])


def handle_putlist(key, value):
    # Return a tuple containing True if the command succeeded and
    # the message to send back to the client.
    return handle_put(key, value)


def handle_getlist(key):
    # Return a tuple containing True if the key contained a list and
    # the message to send back to the client.
    return_value = exists, value = handle_get(key)
    if not exists:
        return return_value
    elif not isinstance(value, list):
        return (
            False,
            'Error: Key [{}] contains non-list value ([{}])'.format(key, value))
    else:
        return return_value
