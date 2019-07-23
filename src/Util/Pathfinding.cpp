#include <cfloat>
#include <cmath>
#include <cstring>
#include <set>
#include <utility>

#include "Util/Pathfinding.h"

namespace bomberman
{
    // check row and column
    bool isValid(const int row, const int column)
    {
        return (row >= 0) && (row < static_cast<int>(tileArrayHeight)) && (column >= 0) &&
               (column < static_cast<int>(tileArrayWidth));
    }

    // check that cell is free
    bool isFreeCell(const Tile (&grid)[tileArrayHeight][tileArrayWidth], const int row, const int column)
    {
        return grid[row][column] == Tile::Grass || grid[row][column] == Tile::EmptyGrass;
    }

    // check destination
    bool isFinished(const int row, const int column, const std::pair<int, int>& dest)
    {
        return row == dest.first && column == dest.second;
    }

    // calculate heuristic
    double calculateHeuristic(const int row, const int col, const std::pair<int, int>& dest)
    {
        // distance
        return sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second));
    }

    // get first cell of path
    std::pair<int, int> getFirstCell(Cell cellDetails[][tileArrayWidth], std::pair<int, int> dest)
    {
        int row = dest.first;
        int column = dest.second;

        std::stack<std::pair<int, int>> path;

        while(!(cellDetails[row][column].parentRow == row && cellDetails[row][column].parentColumn == column))
        {
            path.push(std::make_pair(row, column));
            const int temp_row = cellDetails[row][column].parentRow;
            const int temp_column = cellDetails[row][column].parentColumn;
            row = temp_row;
            column = temp_column;
        }

        return path.top();
    }

    std::pair<int, int> findBestCell(Tile (&grid)[tileArrayHeight][tileArrayWidth],
                                     const std::pair<int, int>& src, const std::pair<int, int>& dest)
    {
        const std::pair<int, int> ret_val_error = {-1, -1};

        // validate source and destination
        if(!isValid(src.first, src.second) || !isValid(dest.first, dest.second))
        {
            return ret_val_error;
        }

        // check source and destination is free
        if(!isFreeCell(grid, src.first, src.second) || !isFreeCell(grid, dest.first, dest.second))
        {
            return ret_val_error;
        }

        // check that source and destination different
        if(isFinished(src.first, src.second, dest))
        {
            return ret_val_error;
        }

        // list of visited
        bool closedList[tileArrayHeight][tileArrayWidth];
        std::memset(closedList, false, sizeof(closedList));

        // details of cell
        Cell cellDetails[tileArrayHeight][tileArrayWidth];
        // fill it with init values
        int i = 0;
        int j = 0;
        for(i = 0; i < static_cast<int>(tileArrayHeight); i++)
        {
            for(j = 0; j < static_cast<int>(tileArrayWidth); j++)
            {
                cellDetails[i][j].f = FLT_MAX;
                cellDetails[i][j].g = FLT_MAX;
                cellDetails[i][j].h = FLT_MAX;
                cellDetails[i][j].parentRow = -1;
                cellDetails[i][j].parentColumn = -1;
            }
        }

        // add starting node to details
        i = src.first, j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].parentRow = i;
        cellDetails[i][j].parentColumn = j;

        // create an open list with information <f, <i, j>> where f = g + h
        std::set<std::pair<double, std::pair<int, int>>> openList;
        // init with start sell
        openList.insert(std::make_pair(0.0, std::make_pair(i, j)));

        while(!openList.empty())
        {
            // first element
            std::pair<double, std::pair<int, int>> p = *openList.begin();
            // remove it
            openList.erase(openList.begin());
            // add to visited
            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            // 'g', 'h', 'f'
            double gNew, hNew, fNew;

            // where to look for path
            const int directions = 4;
            const int cellDir[directions][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for(int dirIter = 0; dirIter < directions; dirIter++)
            {
                if(isValid(i + cellDir[dirIter][0], j + cellDir[dirIter][1]))
                {
                    // check if finished
                    if(isFinished(i + cellDir[dirIter][0], j + cellDir[dirIter][1], dest))
                    {
                        // Set the Parent of the destination cell
                        cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].parentRow = i;
                        cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].parentColumn = j;
                        return getFirstCell(cellDetails, dest);
                    }
                    // If not visited and free
                    else if(!closedList[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]] &&
                            isFreeCell(grid, i + cellDir[dirIter][0], j + cellDir[dirIter][1]))
                    {
                        // new values
                        gNew = cellDetails[i][j].g + 1.0;
                        hNew = calculateHeuristic(i + cellDir[dirIter][0], j + cellDir[dirIter][1], dest);
                        fNew = gNew + hNew;

                        if(cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].f == FLT_MAX ||
                           cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].f > fNew)
                        {
                            openList.insert(std::make_pair(
                                fNew, std::make_pair(i + cellDir[dirIter][0], j + cellDir[dirIter][1])));

                            // Update the details of this cell
                            cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].f = fNew;
                            cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].g = gNew;
                            cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].h = hNew;
                            cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].parentRow = i;
                            cellDetails[i + cellDir[dirIter][0]][j + cellDir[dirIter][1]].parentColumn = j;
                        }
                    }
                }
            }
        }

        // path not found
        return ret_val_error;
    }
} // namespace bomberman
