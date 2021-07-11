#include "text_editor.h"

TextEditor::TextEditor() {
    editor_.emplace_back("");
    cursor_ = Cursor{0, 0};
}

std::vector<std::string>& TextEditor::GetText() {
    return editor_;
}

Cursor& TextEditor::GetCursor() {
    return cursor_;
}

void TextEditor::ShiftDown() {
    if (cursor_.line_num != editor_.size() - 1) {
        std::string cur_string = editor_[cursor_.line_num];
        std::string next_string = editor_[cursor_.line_num + 1];
        if (cur_string.length() > next_string.length()) {
            cursor_.offset = next_string.length() - 1;
        }
        cursor_.line_num++;
    }
}

void TextEditor::ShiftLeft() {
    if (cursor_.offset == 0) {
        if (cursor_.line_num != 0) {
            std::string prev_string = editor_[cursor_.line_num - 1];
            cursor_.offset = prev_string.length() - 1;
            cursor_.line_num--;
        }
    } else {
        cursor_.offset--;
    }
}

void TextEditor::ShiftRight() {
    std::string cur_string = editor_[cursor_.line_num];
    if (cursor_.offset == cur_string.length()) {
        if (cursor_.line_num != editor_.size() - 1) {
            cursor_.offset = 0;
            cursor_.line_num++;
        }
    } else {
        cursor_.offset++;
    }
}

void TextEditor::ShiftUp() {
    if (cursor_.line_num != 0) {
        std::string cur_string = editor_[cursor_.line_num];
        std::string prev_string = editor_[cursor_.line_num - 1];
        if (cur_string.length() > prev_string.length()) {
            cursor_.offset = prev_string.length() - 1;
        }
        cursor_.line_num--;
    }
}

void TextEditor::Delete() {
    std::shared_ptr<IAction> action = std::make_shared<DelAction>(DelAction(cursor_));
    action->Do(this);
    done_.push(action);
    while (!undone_.empty()) {
        undone_.pop();
    }
}

void TextEditor::PasteNewLine() {
    std::shared_ptr<IAction> action = std::make_shared<NewLineAction>(NewLineAction(cursor_));
    action->Do(this);
    done_.push(action);
    while (!undone_.empty()) {
        undone_.pop();
    }
}

void TextEditor::Type(char symbol) {
    std::shared_ptr<IAction> action = std::make_shared<TypeAction>(TypeAction(cursor_, symbol));
    action->Do(this);
    done_.push(action);
    while (!undone_.empty()) {
        undone_.pop();
    }
}

void TextEditor::Undo() {
    done_.top()->Undo(this);
    undone_.push(done_.top());
    done_.pop();
}

void TextEditor::Redo() {
    if (undone_.empty()) {
        return;
    }
    undone_.top()->Do(this);
    done_.push(undone_.top());
    undone_.pop();
}

void TextEditor::Print(std::ostream& out) const {
    for (size_t i = 0; i < editor_.size() - 1; ++i) {
        out << editor_[i] << std::endl;
    }
    out << editor_.back();
}
