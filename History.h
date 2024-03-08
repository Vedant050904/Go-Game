//
//  History.h
//
//  A module to keep track of the previous game positions.
//

#pragma once

#include "BoardValue.h"
#include "Board.h"



struct HistoryNode
{
	Board board;
	HistoryNode* p_next;
};

HistoryNode* copyLinkedList (const HistoryNode* p_old_head_in);
void destroyLinkedList (HistoryNode* p_head_in);



class History
{
public:
	History ();
	History (const History& history_in);
	~History ();
	History& operator= (const History& history_in);

	bool isAtLeast1Long () const;
	bool isAtLeast2Long () const;
	bool isAtLeast3Long () const;
	const Board& getFirst () const;
	const Board& getSecond () const;
	bool isInList (const Board& board_in) const;

	void addAtHead (const Board& board_in);
	void removeAtHead ();
	void removeAll ();

private:
	HistoryNode* p_head;
};

