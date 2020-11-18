template <class T>
Grid<T>::Grid():
	Grid(
		(T)0,
		(T)0,
		(T)0,
		0,
		0
	)
{
	UpdateData();
}

template <class T>
Grid<T>::Grid(T cellWidth, T cellHeight, T lineThickness, int rows, int cols):
	im_Data(),
	im_CellWidth(cellWidth),
	im_CellHeight(cellHeight),
	im_LineThickness(lineThickness),
	im_Rows(rows),
	im_Cols(cols)
{
	UpdateData();
}

template <class T>
int Grid<T>::CalcAmtOfHorizLines() const{
	return im_Rows + 1;
}

template <class T>
int Grid<T>::CalcAmtOfVertLines() const{
	return im_Cols + 1;
}

template <class T>
T Grid<T>::CalcWidth() const{
	return im_Cols * im_CellWidth + (T)CalcAmtOfVertLines() * im_LineThickness;
}

template <class T>
T Grid<T>::CalcHeight() const{
	return im_Rows * im_CellHeight + (T)CalcAmtOfHorizLines() * im_LineThickness;
}

template <class T>
const std::vector<std::vector<bool>>& Grid<T>::GetData() const{
	return im_Data;
}

template <class T>
T Grid<T>::GetCellWidth() const{
	return im_CellWidth;
}

template <class T>
T Grid<T>::GetCellHeight() const{
	return im_CellHeight;
}

template <class T>
T Grid<T>::GetLineThickness() const{
	return im_LineThickness;
}

template <class T>
int Grid<T>::GetRows() const{
	return im_Rows;
}

template <class T>
int Grid<T>::GetCols() const{
	return im_Cols;
}

template <class T>
void Grid<T>::SetData(const bool data, const ptrdiff_t& row, const ptrdiff_t& col){
	im_Data[row][col] = data;
}

template <class T>
void Grid<T>::SetCellWidth(T cellWidth){
	im_CellWidth = cellWidth;
}

template <class T>
void Grid<T>::SetCellHeight(T cellHeight){
	im_CellHeight = cellHeight;
}

template <class T>
void Grid<T>::SetLineThickness(T lineThickness){
	im_LineThickness = lineThickness;
}

template <class T>
void Grid<T>::SetRows(int rows){
	im_Rows = rows;
	UpdateData();
}

template <class T>
void Grid<T>::SetCols(int cols){
	im_Cols = cols;
	UpdateData();
}

template <class T>
void Grid<T>::UpdateData(){
	std::vector<std::vector<bool>> oldData = im_Data; //Make copy of data
	im_Data = std::vector<std::vector<bool>>(im_Rows);

	///Create vars
	int i, j;
	const size_t oldDataSize = oldData.size();

	for(i = 0; i < im_Rows; ++i){
		im_Data[i] = std::vector<bool>(im_Cols);
		for(j = 0; j < im_Cols; ++j){
			im_Data[i][j] = false; //All data becomes false
		}
	}

	for(i = 0; i < (im_Rows < (int)oldDataSize ? im_Rows : (int)oldDataSize); ++i){
		const size_t oldAmtOfCols = oldData[i].size();
		for(j = 0; j < (im_Cols < (int)oldAmtOfCols ? im_Cols : (int)oldAmtOfCols); ++j){
			im_Data[i][j] = oldData[i][j];
		}
	}
}