#include "../Note.h"
#include "../NoteCollection.h"
#include "gtest/gtest.h"

TEST(Note, Create_Note_Successfully) {
    const auto note = new Note("Note1", "Content1");
    EXPECT_EQ(note -> getTitle(), "Note1");
    EXPECT_EQ(note -> getContent(), "Content1");
    EXPECT_EQ(note -> getLocked(), false);
}

TEST(Note, Note_Public_Methods) {
    const auto note = new Note("Note1", "Content1");

    note -> setLocked(true);
    note -> setTitle("NewTitle");
    note -> setContent("NewContent");

    EXPECT_EQ(note -> getTitle(), "Note1");
    EXPECT_EQ(note -> getContent(), "Content1");
}

TEST(NoteCollection, Remove_Note_Unseccessfully) {
    auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
    EXPECT_EQ(noteCollection -> getNote(0), nullptr);

    EXPECT_THROW(noteCollection -> removeNote(0, noteCollection), std::out_of_range);
    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
}

TEST(NoteCollection, Add_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note = make_shared<Note>("Note1", "Content1");
    noteCollection->addNote(note, noteCollection);

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 1);
    EXPECT_NE(noteCollection -> getNote(0), nullptr);
    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), note -> getTitle());
}

TEST(NoteCollection, Add_and_Remove_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note = make_shared<Note>("Note1", "Content1");
    noteCollection -> addNote(note, noteCollection);
    noteCollection -> removeNote(0, noteCollection);

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
    EXPECT_EQ(noteCollection -> getNote(0), nullptr);
}

TEST(NoteCollection, Edit_Note_Unsuccessfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", true);

    noteCollection->addNote(note1, noteCollection);
    EXPECT_THROW(noteCollection -> editNote(0, "Note4", "Content4"), std::logic_error);

    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), "Note1");
    EXPECT_EQ(noteCollection -> getNote(0) -> getContent(), "Content1");

    EXPECT_NE(noteCollection -> getNote(0) -> getTitle(), "Note4");
    EXPECT_NE(noteCollection -> getNote(0) -> getContent(), "Content4");
}

TEST(NoteCollection, Edit_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1");

    noteCollection->addNote(note1, noteCollection);
    noteCollection -> editNote(0, "Note3", "Content3");

    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), "Note3");
    EXPECT_EQ(noteCollection -> getNote(0) -> getContent(), "Content3");
}