//
//  History.cpp
//

#include "History.h"

#include <cassert>

#include "Board.h"



HistoryNode* copyLinkedList (const HistoryNode* p_old_head_in)
{
	// special case: no elements
	if(p_old_head_in == nullptr)
		return nullptr;

	HistoryNode* p_new_head = new HistoryNode;
	p_new_head->board  = p_old_head_in->board;
	p_new_head->p_next = nullptr;

	const HistoryNode* p_old_current = p_old_head_in;
	HistoryNode*       p_new_current = p_new_head;
	while(p_old_current->p_next != nullptr)
	{
		p_new_current->p_next = new HistoryNode;

		p_old_current = p_old_current->p_next;
		p_new_current = p_new_current->p_next;

		p_new_current->board  = p_old_current->board;
		p_new_current->p_next = nullptr;
	}

	return p_new_head;
}

void destroyLinkedList (HistoryNode* p_head_in)
{
	HistoryNode* p_current = p_head_in;
	while(p_current != nullptr)
	{
		HistoryNode* p_next = p_current->p_next;
		delete p_current;
		p_current = p_next;
	}
}



History :: History ()
{
	p_head = nullptr;
}

History :: History (const History& history_in)
{
	p_head = copyLinkedList(history_in.p_head);
}

History :: ~History ()
{
	destroyLinkedList(p_head);
}

History& History :: operator= (const History& history_in)
{
	if(&history_in != this)
	{
		destroyLinkedList(p_head);
		p_head = copyLinkedList(history_in.p_head);
	}
	return *this;
}



bool History :: isAtLeast1Long () const
{
	if(p_head == nullptr)
		return false;
	return true;
}

bool History :: isAtLeast2Long () const
{
	if(p_head == nullptr)
		return false;
	if(p_head->p_next == nullptr)
		return false;
	return true;
}

bool History :: isAtLeast3Long () const
{
	if(p_head == nullptr)
		return false;
	if(p_head->p_next == nullptr)
		return false;
	if(p_head->p_next->p_next == nullptr)
		return false;
	return true;
}

const Board& History :: getFirst () const
{
	assert(isAtLeast1Long());

	assert(p_head != nullptr);
	return p_head->board;
}

const Board& History :: getSecond () const
{
	assert(isAtLeast2Long());

	assert(p_head != nullptr);
	assert(p_head->p_next != nullptr);
	return p_head->p_next->board;
}

bool History :: isInList (const Board& board_in) const
{
	for(const HistoryNode* p_current = p_head;
	    p_current != nullptr;
	    p_current = p_current->p_next)
	{
		if(p_current->board == board_in)
			return true;
	}
	return false;
}



void History :: addAtHead (const Board& board_in)
{
	HistoryNode* p_new = new HistoryNode;
	p_new->board  = board_in;
	p_new->p_next = p_head;
	p_head = p_new;
}

void History :: removeAtHead ()
{
	assert(isAtLeast1Long());

	assert(p_head != nullptr);
	HistoryNode* p_temp = p_head->p_next;
	delete p_head;
	p_head = p_temp;
}

void History :: removeAll ()
{
	destroyLinkedList(p_head);
	p_head = nullptr;
}

