#pragma once

#include <memory>
#include <stack>
#include <string>
#include "actions.h"

class TextEditor {
private:
    Cursor cursor_;
    std::vector<std::string> editor_;
    std::stack<std::shared_ptr<IAction>> done_;
    std::stack<std::shared_ptr<IAction>> undone_;

public:
    TextEditor();
    void ShiftLeft();
    void ShiftRight();
    void ShiftDown();
    void ShiftUp();
    void Delete();
    void PasteNewLine();
    void Type(char);
    void Undo();
    void Redo();
    void Print(std::ostream&) const;
    std::vector<std::string>& GetText();
    Cursor& GetCursor();
};
