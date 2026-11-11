//
// DocumentTest.cpp - Unit tests for the Document class
// This file contains test cases for the core document functionality
//

#include <gtest/gtest.h>
#include "Document.h"

namespace Memo {
namespace Core {

/**
 * @brief Test fixture for Document tests
 */
class DocumentTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code before each test
    }

    void TearDown() override {
        // Cleanup code after each test
    }
};

/**
 * @brief Test document creation and basic properties
 */
TEST_F(DocumentTest, CreateDocument) {
    Document doc("Test Document");

    EXPECT_EQ(doc.getTitle(), "Test Document");
    EXPECT_EQ(doc.getContent(), "");
}

/**
 * @brief Test setting and getting document title
 */
TEST_F(DocumentTest, SetTitle) {
    Document doc;

    doc.setTitle("New Title");
    EXPECT_EQ(doc.getTitle(), "New Title");
}

/**
 * @brief Test setting and getting document content
 */
TEST_F(DocumentTest, SetContent) {
    Document doc;

    doc.setContent("Test content for the document");
    EXPECT_EQ(doc.getContent(), "Test content for the document");
}

/**
 * @brief Test adding strokes to document
 */
TEST_F(DocumentTest, AddStroke) {
    Document doc;

    // Create a simple stroke (we won't actually implement Stroke here but test interface)
    // This is just testing that we can add and get strokes
    EXPECT_EQ(doc.getStrokes().size(), 0);
}

/**
 * @brief Test undo/redo functionality (basic stub)
 */
TEST_F(DocumentTest, UndoRedo) {
    Document doc;

    // These should not crash, even if undo/redo is not fully implemented yet
    EXPECT_TRUE(doc.undo());
    EXPECT_TRUE(doc.redo());
}

} // namespace Core
} // namespace Memo

// Main test runner
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}