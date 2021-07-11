#include "actions.h"
#include "text_editor.h"

IAction::IAction(Cursor cursor) : cursor(cursor) {
}

TypeAction::TypeAction(Cursor cursor, char symbol) : IAction(cursor), symbol_(symbol) {
}

void TypeAction::Do(TextEditor* editor) const {
    auto& text_editor = editor->GetText();
    if (symbol_ == '\n') {
        NewLineAction action = NewLineAction(cursor);
        action.Do(editor);
    } else {
        text_editor[cursor.line_num].insert(text_editor[cursor.line_num].begin() + cursor.offset, symbol_);
        editor->GetCursor().line_num = cursor.line_num;
        editor->GetCursor().offset = cursor.offset + 1;
    }
}

void TypeAction::Undo(TextEditor* editor) const {
    auto& text_editor = editor->GetText();
    if (symbol_ == '\n') {
        NewLineAction action = NewLineAction(cursor);
        action.Undo(editor);
    } else {
        text_editor[cursor.line_num].erase(text_editor[cursor.line_num].begin() + cursor.offset);
        editor->GetCursor().line_num = cursor.line_num;
        editor->GetCursor().offset = cursor.offset;
    }
}

DelAction::DelAction(Cursor cursor) : IAction(cursor), symbol_('\n') {
}

void DelAction::Do(TextEditor* editor) const {
    auto& text_editor = editor->GetText();
    if (cursor.offset == text_editor[cursor.line_num].length()) {
        if (cursor.line_num == text_editor.size() - 1) {
            return;
        }
        NewLineAction action = NewLineAction(cursor);
        action.Undo(editor);
    } else {
        symbol_ = text_editor[cursor.line_num][cursor.offset];
        TypeAction action = TypeAction(cursor, symbol_);
        action.Undo(editor);
    }
}

void DelAction::Undo(TextEditor* editor) const {
    if (symbol_ == '\n') {
        NewLineAction action = NewLineAction(cursor);
        action.Do(editor);
    } else {
        TypeAction action = TypeAction(cursor, symbol_);
        action.Do(editor);
    }
}

NewLineAction::NewLineAction(Cursor cursor) : IAction(cursor) {
}

void NewLineAction::Do(TextEditor* editor) const {
    auto& text_editor = editor->GetText();
    std::string new_string = text_editor[cursor.line_num].substr(cursor.offset);
    std::string cut_string =
        text_editor[cursor.line_num].substr(0, text_editor[cursor.line_num].length() - new_string.length());
    text_editor[cursor.line_num] = cut_string;
    text_editor.insert(text_editor.begin() + cursor.line_num + 1, new_string);
    editor->GetCursor().line_num = cursor.line_num + 1;
    editor->GetCursor().offset = 0;
}

void NewLineAction::Undo(TextEditor* editor) const {
    auto& text_editor = editor->GetText();
    text_editor[cursor.line_num] += text_editor[cursor.line_num + 1];
    text_editor.erase(text_editor.begin() + cursor.line_num + 1);
    editor->GetCursor().line_num = cursor.line_num;
    editor->GetCursor().offset = cursor.offset;
}
