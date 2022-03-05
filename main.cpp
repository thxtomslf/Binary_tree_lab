#include <iostream>


struct Binary_tree {
    int value;
    Binary_tree *left;
    Binary_tree *right;

};


Binary_tree* search(Binary_tree *tree, int value) {
    if (tree == nullptr) {
        std::cout << "Value wasn't found.";
        return nullptr;
    }
    if (tree->value == value) {
        std::cout << '(' << value << ')';
        return tree;
    }
    std::cout << "(" << tree->value << ")" << " -> ";
    if (tree->value > value) {
        search(tree->left, value);
    } else {
        search(tree->right, value);
    }
}


void push(int value_to_add, Binary_tree *&tree) {
    if (tree == nullptr) {
        tree = new Binary_tree;
        tree->value = value_to_add;
        tree->left = nullptr;
        tree->right = nullptr;
        return;
    }
    if (value_to_add < tree->value) {
        push(value_to_add, tree->left);
    } else if (value_to_add > tree->value) {
        push(value_to_add, tree->right);
    }
}


Binary_tree* find_parent(Binary_tree* tree, int value, Binary_tree *sub) {
    if (tree == sub) {
        return nullptr;
    }

    if (tree->value >= value) {
        if (tree->left->value == value) {
            return tree;
        }
        find_parent(tree->left, value, sub);
    } else {
        if (tree->right->value == value) {
            return tree;
        }
        find_parent(tree->right, value, sub);
    }

}


Binary_tree* find_most_left(Binary_tree *tree) {
    while (tree->left != nullptr) {
        tree = tree->left;
    }
    return tree;
}


void delete_element(Binary_tree *&tree, int value) {
    Binary_tree* sub_tree = search(tree, value);
    if (sub_tree == nullptr) {
        return;
    }


    Binary_tree* parent = find_parent(tree, value, sub_tree);

    if (sub_tree->right == nullptr && sub_tree->left == nullptr) {
        if (parent != nullptr) {
            if (parent->left != nullptr && parent->left->value == value) {
                parent->left = nullptr;
            } else if (parent->right != nullptr && parent->right->value == value) {
                parent->right = nullptr;
            }
            delete sub_tree;
        } else {
            delete sub_tree;
            tree = nullptr;
            return;
        }

    } else if (sub_tree->right == nullptr && sub_tree->left != nullptr) {
        Binary_tree *pointer_to_del = sub_tree;
        sub_tree = sub_tree->left;
        if (parent != nullptr) {
            if (parent->left->value == value) {
                delete parent->left;
                parent->left = sub_tree;
            } else if (parent->right->value == value) {
                delete parent->right;
                parent->right = sub_tree;
            }
        } else {
            tree = sub_tree;
            delete pointer_to_del;
        }
    } else if (sub_tree->right != nullptr && sub_tree->left == nullptr) {
        Binary_tree *pointer_to_del = sub_tree;
        sub_tree = sub_tree->right;
        if (parent != nullptr) {
            if (parent->left->value == value) {
                delete parent->left;
                parent->left = sub_tree;
            } else if (parent->right->value == value) {
                delete parent->right;
                parent->right = sub_tree;
            }
        } else {
            tree = sub_tree;
            delete pointer_to_del;
        }
    } else if (sub_tree->right != nullptr && sub_tree->left != nullptr) {
        if (sub_tree->right->left == nullptr) {
            Binary_tree *parent_sub_tree = sub_tree;
            sub_tree = sub_tree->right;
            if (parent != nullptr) {
                if (parent->left->value == value) {
                    parent->left = sub_tree;
                    sub_tree->left = parent_sub_tree->left;
                } else if (parent->right->value == value) {
                    parent->right = sub_tree;
                    sub_tree->left = parent_sub_tree->left;
                }
            } else {
                tree = sub_tree;
                tree->left = parent_sub_tree->left;
            }
            delete parent_sub_tree;
        } else {
            Binary_tree *leftest_tree = find_most_left(sub_tree->right);
            leftest_tree->left = sub_tree->left;
            Binary_tree *parent_sub_tree = sub_tree;
            sub_tree = sub_tree->right;
            if (parent != nullptr) {
                if (parent->left->value == value) {
                    parent->left = sub_tree;
                } else if (parent->right->value == value) {
                    parent->right = sub_tree;
                }
            } else {
                tree = sub_tree;
            }
            delete parent_sub_tree;
            std::cout << ' ';
        }
    }
}

void prefix_print(Binary_tree *tree) {
    if (tree == nullptr) {
        return;
    }
    std::cout << tree->value << ' ';
    prefix_print(tree->left);
    prefix_print(tree->right);
}

void infix_print(Binary_tree *tree) {
    if (tree == nullptr) {
        return;
    }
    infix_print(tree->left);
    std::cout << tree->value << ' ';
    infix_print(tree->right);
}

void postfix_print(Binary_tree *tree) {
    if (tree == nullptr) {
        return;
    }
    postfix_print(tree->left);
    postfix_print(tree->right);
    std::cout << tree->value << ' ';
}



int main() {
    Binary_tree *tree = nullptr;
    push(8, tree);
    push(10, tree);
    push(13, tree);
    push(14, tree);
    std::cout << "Call functions:\ninfix_print - \"inf_p\"\n"
                 "postfix_print - \"post_p\"\n"
                 "prefix_print - \"pre_p\"\n"
                 "add value - \"a_v\"\n"
                 "delete value - \"del_v\"\n"
                 "search value - \"s_v\"\n";

    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "inf_p") {
            infix_print(tree);
            std::cout << '\n';
        } else if (input == "post_p") {
            postfix_print(tree);
            std::cout << '\n';
        } else if (input == "pre_p") {
            prefix_print(tree);
            std::cout << '\n';
        } else if (input == "a_v") {
            int value;
            std::cin >> value;
            std::cin.ignore();
            push(value, tree);
        } else if (input == "del_v") {
            int value;
            std::cin >> value;
            std::cin.ignore();
            delete_element(tree, value);
            std::cout << '\n';
        } else if (input == "s_v") {
            int value;
            std::cin >> value;
            std::cin.ignore();
            search(tree, value);
            std::cout << '\n';
        } else if (input == "exit") {
            break;
        }
        std::cout << "Call_functions\n";
    }
}
