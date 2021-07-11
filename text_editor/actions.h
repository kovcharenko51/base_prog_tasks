#pragma once

#include <iostream>
#include <vector>

class TextEditor;

struct Cursor {
    size_t line_num;
    size_t offset;
};

class IAction {
protected:
    const Cursor cursor;

public:
    explicit IAction(Cursor);
    virtual ~IAction() = default;
    virtual void Do(TextEditor*) const = 0;
    virtual void Undo(TextEditor*) const = 0;
};

class TypeAction : public IAction {
private:
    char symbol_;

public:
    TypeAction(Cursor, char);
    void Do(TextEditor*) const override;
    void Undo(TextEditor*) const override;
};

class DelAction : public IAction {
private:
    mutable char symbol_;

public:
    explicit DelAction(Cursor);
    void Do(TextEditor*) const override;
    void Undo(TextEditor*) const override;
};

class NewLineAction : public IAction {
public:
    explicit NewLineAction(Cursor);
    void Do(TextEditor*) const override;
    void Undo(TextEditor*) const override;
};
