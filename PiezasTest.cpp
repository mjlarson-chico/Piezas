/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, drop_correct_peiceX)
{
	Piezas test;
	ASSERT_EQ(test.dropPiece(3), X);
}

TEST(PiezasTest, drop_correct_peiceO)
{
	Piezas test;
	test.dropPiece(1);
	ASSERT_EQ(test.dropPiece(3), O);
}

TEST(PiezasTest, drop_out_of_bounds)
{
	Piezas test;
	ASSERT_EQ(test.dropPiece(-1), Invalid);
}

TEST(PiezasTest, drop_full_col)
{
	Piezas test;
	test.dropPiece(0);
	test.dropPiece(0);
	test.dropPiece(0);
	ASSERT_EQ(test.dropPiece(0), Blank);
}

TEST(PiezasTest, peice_at_correctX)
{
	Piezas test;
	test.dropPiece(1);
	ASSERT_EQ(test.pieceAt(0,1), X);
}

TEST(PiezasTest, peice_at_correctO)
{
	Piezas test;
	test.dropPiece(1);
	test.dropPiece(2);
	ASSERT_EQ(test.pieceAt(0,2), O);
}

TEST(PiezasTest, peice_at_out_of_bounds_row)
{
	Piezas test;
	ASSERT_EQ(test.pieceAt(-1,1), Invalid);
}

TEST(PiezasTest, peice_at_out_of_bounds_col)
{
	Piezas test;
	ASSERT_EQ(test.pieceAt(1,-1), Invalid);
}

TEST(PiezasTest, resetBoard)
{
	Piezas test;

	test.dropPiece(2);

	test.reset();

	ASSERT_EQ(test.pieceAt(0,2), Blank);
}

TEST(PiezasTest, gamestate_not_over)
{
	Piezas test;
	test.dropPiece(2);
	ASSERT_EQ(test.gameState(), Invalid);
}

TEST(PiezasTest, gamestate_tied)
{
	Piezas test;

	for( unsigned i = 0; i < BOARD_COLS; i++)
	{
		for( unsigned j = 0; j < BOARD_ROWS; j++ )
		{
			test.dropPiece(i);
		}
	}

	ASSERT_EQ(test.gameState(), Blank);
}

TEST(PiezasTest, gamestate_tied)
{
	Piezas test;

	for( unsigned i = 0; i < BOARD_COLS; i++)
	{
		for( unsigned j = 0; j < BOARD_ROWS; j++ )
		{
			test.dropPiece(i);
		}
	}
	ASSERT_EQ(test.gameState(), Blank);
}