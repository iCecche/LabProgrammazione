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
    auto noteCollection = make_shared<NoteCollection>("NoteCollection1");

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
    EXPECT_EQ(noteCollection -> getNote(0), nullptr);

    noteCollection -> removeNote(0, noteCollection);
    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
}

TEST(NoteCollection, test2) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note = make_shared<Note>("Note1", "Content1");
    noteCollection->addNote(note, noteCollection);

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 1);
    EXPECT_NE(noteCollection -> getNote(0), nullptr);
    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), note -> getTitle());
}

TEST(NoteCollection, test3) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note = make_shared<Note>("Note1", "Content1");
    noteCollection->addNote(note, noteCollection);
    noteCollection -> removeNote(0, noteCollection);

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
    EXPECT_EQ(noteCollection -> getNote(0), nullptr);
}

TEST(NoteCollection, test4) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1");
    const auto note2 = make_shared<Note>("Note2", "Content2", true);

    noteCollection->addNote(note1, noteCollection);
    noteCollection->addNote(note2, noteCollection);

    noteCollection -> editNote(0, "Note3", "Content3");
    noteCollection -> editNote(1, "Note4", "Content4");

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 2);
    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), "Note3");
    EXPECT_EQ(noteCollection -> getNote(0) -> getContent(), "Content3");

    EXPECT_NE(noteCollection -> getNote(1) -> getTitle(), "Note4");
    EXPECT_NE(noteCollection -> getNote(1) -> getContent(), "Content4");

    note2 -> setLocked(false);
    noteCollection -> editNote(0, "Note3", "Content3");
    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), "Note3");
    EXPECT_EQ(noteCollection -> getNote(0) -> getContent(), "Content3");

    noteCollection -> editNote(0, std::nullopt, "NewContent");
    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), "Note3");
    EXPECT_EQ(noteCollection -> getNote(0) -> getContent(), "NewContent");

    noteCollection -> editNote(0, "NewTitle");
    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), "NewTitle");
    EXPECT_EQ(noteCollection -> getNote(0) -> getContent(), "NewContent");
}