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

TEST(NoteCollection, test4) {
    const auto noteCollection = new NoteCollection("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1");
    const auto note2 = make_shared<Note>("Note2", "Content2", true);

    noteCollection->addNote(note1);
    noteCollection->addNote(note2);

    noteCollection -> editNote("Note1", "Note3", "Content3");
    noteCollection -> editNote("Note2", "Note4", "Content4");

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 2);
    EXPECT_EQ(noteCollection -> getNote("Note3") -> getTitle(), "Note3");
    EXPECT_EQ(noteCollection -> getNote("Note3") -> getContent(), "Content3");

    EXPECT_NE(noteCollection -> getNote("Note2") -> getTitle(), "Note4");
    EXPECT_NE(noteCollection -> getNote("Note2") -> getContent(), "Content4");

    noteCollection -> editNote("Note3");
    EXPECT_EQ(noteCollection -> getNote("Note3") -> getTitle(), "Note3");
    EXPECT_EQ(noteCollection -> getNote("Note3") -> getContent(), "Content3");

    noteCollection -> editNote("Note3", std::nullopt, "NewContent");
    EXPECT_EQ(noteCollection -> getNote("Note3") -> getTitle(), "Note3");
    EXPECT_EQ(noteCollection -> getNote("Note3") -> getContent(), "NewContent");

    noteCollection -> editNote("Note3", "NewTitle");
    EXPECT_EQ(noteCollection -> getNote("NewTitle") -> getTitle(), "NewTitle");
    EXPECT_EQ(noteCollection -> getNote("NewTitle") -> getContent(), "NewContent");

}