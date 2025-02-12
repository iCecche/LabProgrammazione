#include "../Note.h"
#include "../NoteCollection.h"
#include "gtest/gtest.h"

TEST(Note, test1) {
    const auto note = new Note("Note1", "Content1");
    EXPECT_EQ(note -> getTitle(), "Note1");
    EXPECT_EQ(note -> getContent(), "Content1");
    EXPECT_EQ(note -> getLocked(), false);
}

TEST(Note, test2) {
    const auto note = new Note("Note1", "Content1");

    note -> setLocked(true);
    note -> setTitle("NewTitle");
    note -> setContent("NewContent");

    EXPECT_EQ(note -> getTitle(), "Note1");
    EXPECT_EQ(note -> getContent(), "Content1");
}

TEST(NoteCollection, test1) {
    const auto noteCollection = new NoteCollection("NoteCollection1");

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
    EXPECT_EQ(noteCollection -> getNote("a title"), nullptr);

    noteCollection -> removeNote("Note1");
    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
}

TEST(NoteCollection, test2) {
    const auto noteCollection = new NoteCollection("NoteCollection1");
    const auto note = make_shared<Note>("Note1", "Content1");
    noteCollection->addNote(note);

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 1);
    EXPECT_NE(noteCollection -> getNote("Note1"), nullptr);
    EXPECT_EQ(noteCollection -> getNote("Note1") -> getTitle(), note -> getTitle());
}

TEST(NoteCollection, test3) {
    const auto noteCollection = new NoteCollection("NoteCollection1");
    const auto note = make_shared<Note>("Note1", "Content1");
    noteCollection->addNote(note);
    noteCollection -> removeNote("Note1");

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
    EXPECT_EQ(noteCollection -> getNote("Note1"), nullptr);
}