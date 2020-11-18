#pragma once

template <class T>
class Grid final{ //Row-major order
public:
	Grid<T>();
	Grid<T>(T cellWidth, T cellHeight, T lineThickness, int rows, int cols);
	~Grid<T>() = default;

	int CalcAmtOfHorizLines() const;
	int CalcAmtOfVertLines() const;
	T CalcWidth() const;
	T CalcHeight() const;

	///Getters
	const std::vector<std::vector<bool>>& GetData() const;
	T GetCellWidth() const;
	T GetCellHeight() const;
	T GetLineThickness() const;
	int GetRows() const;
	int GetCols() const;

	///Setters
	void SetData(const bool data, const ptrdiff_t& row, const ptrdiff_t& col);
	void SetCellWidth(T cellWidth);
	void SetCellHeight(T cellHeight);
	void SetLineThickness(T lineThickness);
	void SetRows(int rows);
	void SetCols(int cols);
private:
	std::vector<std::vector<bool>> im_Data;

	T im_CellWidth;
	T im_CellHeight;
	T im_LineThickness;

	int im_Rows;
	int im_Cols;

	void UpdateData();
};

#include "Grid.inl"