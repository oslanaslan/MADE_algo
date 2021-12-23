"""
Lexicographical Parser Module

"""

from typing import Any


class Token:
    """
    Token class

    """

    def __init__(self, name: str = None, value: int = None) -> None:
        """Init all statements"""

        # For fast comparing like: if token.is_int ...
        self.is_right_scope: bool = True if name == 'right_scope' else False
        self.is_left_scope: bool = True if name == 'left_scope' else False
        self.is_int: bool = True if name == 'int' else False
        # For comparing by name of token type
        self.name: str = name
        self.value: int = value

    def __call__(self, *args: Any, **kwds: Any) -> str:
        """Get token name"""
        if self.name:
            return self.name
        else:
            raise ValueError

    def __eq__(self, token: object) -> bool:
        """Compare tokens"""
        if not isinstance(token, Token):
            raise ValueError
        if token.name:
            return self.is_token(token.name)

    def __ne__(self, token: object) -> bool:
        """Compare tokens"""
        return not self.__eq__(token)

    def __hash__(self) -> int:
        return self.value.__hash__()

    def __repr__(self) -> str:
        """Print token"""
        return self.name

    def __str__(self) -> str:
        """Token to str"""
        return self.name

    def is_token(self, token_name: str) -> bool:
        """Check if this token is type of 'token_name'"""
        if self.name:
            if self.name == token_name:
                return True
            return False
        return ValueError


class Lexer:
    """
    Parser for lexicographical parsing

    """

    def __init__(self, input_str: str) -> None:
        """Parser init"""
        self.token_lst = []
        self.input_str = input_str
        self.parse()

    def __len__(self):
        """Get token_lst len"""
        return len(self.token_lst)

    def __iter__(self):
        """Iteration through token_lst"""
        for token in self.token_lst:
            yield token

    def parse(self):
        """Parse self.input_str"""
        pass
