"""
Lexicographical Parser Module

"""

from typing import Any


END_CHAR = '.'

class Token:
    """
    Token base class

    """

    def __init__(self, name: str = None, value: int = None) -> None:
        """Init all statements"""

        # For fast comparing like: if token.is_int ...
        self.is_right_scope: bool = True if name == 'right_scope' else False
        self.is_left_scope: bool = True if name == 'left_scope' else False
        self.is_int: bool = True if name == 'int' else False
        self.is_mul = True if name == 'mul' else False
        self.is_add = True if name == 'add' else False
        self.is_sub = True if name == 'sub' else False
        self.is_eof = True if name == END_CHAR else False
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
        self.iter = 0
        self.token_iter = 0
        self.parse()

    def __len__(self) -> int:
        """Get token_lst len"""
        return len(self.token_lst)

    def __iter__(self) -> Token:
        """Iteration through token_lst"""
        for token in self.token_lst:
            yield token

    def current_char(self) -> str:
        return self.input_str[self.iter]

    def next_char(self) -> str:
        self.iter += 1
        return self.input_str[self.iter - 1]

    def next_token(self) -> Token:
        if self.token_iter >= len(self.token_lst):
            return Token(END_CHAR)
        self.token_iter += 1
        return self.token_lst[self.token_iter - 1]

    def current_token(self) -> Token:
        if self.token_iter >= len(self.token_lst):
            return Token(END_CHAR)
        return self.token_lst[self.token_iter]

    def is_eof(self) -> bool:
        return (self.token_iter >= len(self.token_lst))

    def parse_digits_(self) -> None:
        '''Parse digit tokens'''
        token = Token('int', '')
        while self.current_char().isdigit():
            token.value += self.next_char()
        self.token_lst.append(token)

    def parse(self) -> None:
        """Parse self.input_str"""
        while self.current_char() != END_CHAR:
            if self.current_char() == '(':
                self.token_lst.append(Token('left_scope', self.next_char()))
            elif self.current_char() == ')':
                self.token_lst.append(Token('right_scope', self.next_char()))
            elif self.current_char() == '+':
                self.token_lst.append(Token('add', self.next_char()))
            elif self.current_char() == '-':
                self.token_lst.append(Token('sub', self.next_char()))
            elif self.current_char() == '*':
                self.token_lst.append(Token('mul', self.next_char()))
            else:
                self.parse_digits_()

    def print_tokens(self) -> None:
        for token in self.token_lst:
            print(token.value)


class BaseNode:
    """
    Tree node with operands or operators

    """

    id_ctr: int = 0

    def __init__(self, value: int = None, left_child = None, right_child = None) -> None:
        self.is_exp = False
        self.is_sum = False
        self.is_prod = False
        self.is_term = False
        self.is_num = False
        self.is_sub = False
        self.value = value
        self.id = BaseNode.id_ctr
        self.left_child = left_child
        self.right_child = right_child
        BaseNode.id_ctr += 1


class Exp(BaseNode):
    """
    Exp node
    
    """

    def __init__(self, value: int = None, left_child=None, right_child=None) -> None:
        super().__init__(value=value, left_child=left_child, right_child=right_child)
        self.is_exp = True

    def __repr__(self) -> str:
        return 'Exp'


class Sum(BaseNode):
    """
    Sum Node

    """

    def __init__(self, value: int = None, left_child=None, right_child=None) -> None:
        super().__init__(value=value, left_child=left_child, right_child=right_child)
        self.is_sum = True
    
    def __repr__(self) -> str:
        return "Sum"


class Sub(BaseNode):
    """
    Sub Node

    """

    def __init__(self, value: int = None, left_child=None, right_child=None) -> None:
        super().__init__(value=value, left_child=left_child, right_child=right_child)
        self.is_sub = True
    
    def __repr__(self) -> str:
        return "Sub"


class Prod(BaseNode):
    """
    Prod Node

    """

    def __init__(self, value: int = None, left_child=None, right_child=None) -> None:
        super().__init__(value=value, left_child=left_child, right_child=right_child)
        self.is_prod = True

    def __repr__(self) -> str:
        return 'Prod'


class Term(BaseNode):
    """
    Term Node

    """

    def __init__(self, value: int = None, left_child=None, right_child=None) -> None:
        super().__init__(value=value, left_child=left_child, right_child=right_child)
        self.is_term = True

    def __repr__(self) -> str:
        return "Term"


class Num(BaseNode):
    """
    Num Node

    """

    def __init__(self, value: int = None, left_child=None, right_child=None) -> None:
        super().__init__(value=value, left_child=left_child, right_child=right_child)
        self.is_num = True

    def __repr__(self) -> str:
        return "Num"


class Tree:
    """
    Tree class for evaluating

    """

    def __init__(self, root: Exp, const_values: dict = None) -> None:
        self.const_values = const_values or dict()
        self.root = root
    
    def calculate_subtree(self, node: BaseNode) -> int:
        if not node:
            return None
        if node.is_num:
            return int(node.value)
        if node.is_exp or node.is_term:
            return self.calculate_subtree(node.left_child)
        if node.is_sum:
            left_value = self.calculate_subtree(node.left_child)
            right_value = self.calculate_subtree(node.right_child)
            if not left_value and not right_value:
                return None
            res = (left_value or 0) + (right_value or 0)
            return res
        if node.is_sub:
            left_value = self.calculate_subtree(node.left_child)
            right_value = self.calculate_subtree(node.right_child)
            if not left_value and not right_value:
                return None
            res = (left_value or 0) - (right_value or 0)
            return res
        if node.is_prod:
            left_value = self.calculate_subtree(node.left_child)
            right_value = self.calculate_subtree(node.right_child)
            if not left_value and not right_value:
                return None
            res = (left_value or 1) * (right_value or 1)
            return res
        return None

    def evaluate(self) -> int:
        """Evaluate input expression"""
        value = self.calculate_subtree(self.root)
        return value

    def print_tree(self) -> None:
        node_lst = [self.root]
        new_node_lst = []

        while len(node_lst) > 0 or len(new_node_lst) > 0:
            for cur_node in node_lst:
                if cur_node:
                    left_id = cur_node.left_child.id if cur_node.left_child else ''
                    right_id = cur_node.right_child.id if cur_node.right_child else ''
                    print(f"{cur_node}({cur_node.id}) {cur_node.value} - l -> {left_id}, - r -> {right_id}", end='\t')
                    new_node_lst.append(cur_node.left_child)
                    new_node_lst.append(cur_node.right_child)
            node_lst = new_node_lst
            new_node_lst = []

            print()


class Parser:
    """
    Parser for tokens

    """

    def __init__(self, lexer: Lexer) -> None:
        self.lexer = lexer
        self.tree = None

    def parse_exp(self):
        if not self.lexer.current_token().is_right_scope and not self.lexer.is_eof():
            return self.parse_sum()


    def parse_sum(self):
        current_node = Sum()
        current_node.left_child = self.parse_prod()
        sum_lst = []
        sum_val_lst = []
        sum_sign_lst = []
        current_token = self.lexer.current_token()
        while current_token.is_add or current_token.is_sub:
            current_token = self.lexer.next_token()
            sum_lst.append(self.parse_sum())
            sum_val_lst.append(current_token.name)
            sum_sign_lst.append(True if current_token.is_add else False)
        for parsed_sum, parsed_val, parsed_sign in zip(sum_lst, sum_val_lst, sum_sign_lst):
            current_node.right_child = parsed_sum
            current_node.value = parsed_val
            new_node = Sum() if parsed_sign else Sub()
            new_node.left_child = current_node
            current_node = new_node

        return current_node

    def parse_prod(self):
        current_node = Prod()
        current_node.left_child = self.parse_term()
        prod_lst = []
        prod_val_lst = []
        current_token = self.lexer.current_token()
        while current_token.is_mul:
            current_token = self.lexer.next_token()
            prod_lst.append(self.parse_prod())
            prod_val_lst.append(current_token.name)
            current_token
        for parse_prod, parsed_val in zip(prod_lst, prod_val_lst):
            current_node.right_child = parse_prod
            current_node.value = parsed_val
            new_node = Prod()
            new_node.left_child = current_node
            current_node = new_node

        return current_node

    def parse_term(self):
        if self.lexer.current_token().is_left_scope:
            current_node = Exp()
            self.lexer.next_token()
            current_node.left_child = self.parse_exp()
            end_token = self.lexer.next_token()
            return current_node
        elif self.lexer.current_token().is_int:
            current_node = Term()
            current_node.left_child = self.parse_num()
            return current_node
        else:
            None

    def parse_num(self):
        current_node = Num()
        current_node.value = self.lexer.next_token().value
        return current_node

    def parse(self) -> None:
        return self.parse_exp()

def main() -> None:
    input_str = input()
    parser = Parser(Lexer(input_str))
    # parser.lexer.print_tokens()
    root = parser.parse()
    tree = Tree(root)
    # tree.print_tree()
    print(tree.evaluate())


if __name__ == '__main__':
    main()