//
// Created by Alessio Ceccherini on 17/04/25.
//

#include "../src/Note.h"
#include "../src/NoteCollection.h"
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