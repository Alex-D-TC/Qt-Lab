#pragma once

template<typename T>
class UndoAction {

public:

	UndoAction() = default;
	virtual void doUndo() = 0;

};