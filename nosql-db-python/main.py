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
