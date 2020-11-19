#include "EventGridDataChanged.h"

EventGridDataChanged::EventGridDataChanged(const int blockRow, const int blockCol):
	Event(EventID::EventGridDataChanged),
	im_BlockRow(blockRow),
	im_BlockCol(blockCol)
{
}

int EventGridDataChanged::GetBlockRow() const{
	return im_BlockRow;
}

int EventGridDataChanged::GetBlockCol() const{
	return im_BlockCol;
}

EventGridDataChanged* EventGridDataChanged::Clone() const{
	return new EventGridDataChanged(*this);
}