/*
 * Copyright 12/06/2025 https://github.com/su8/0vernn
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <ncurses.h>

char brightnessToChar(unsigned char brightness);

int main(int argc, char *argv[]) {
  if (argc < 2) { std::cerr << "Usage: " << argv[0] << " <image_path>" << std::endl; return EXIT_FAILURE; }

  // Load image using OpenCV
  cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  if (img.empty()) { std::cerr << "Error: Could not load image." << std::endl; return EXIT_FAILURE; }

  // Initialize ncurses
  initscr();
  noecho();
  curs_set(0);

  int termRows, termCols;
  getmaxyx(stdscr, termRows, termCols);

  // Resize image to fit terminal
  cv::Mat resized;
  cv::resize(img, resized, cv::Size(termCols, termRows));

  // Display image as ASCII
  for (int y = 0; y < resized.rows; y++) {
    for (int x = 0; x < resized.cols; x++) {
      unsigned char pixel = resized.at<uchar>(y, x);
      mvaddch(y, x, brightnessToChar(pixel));
    }
  }

  refresh();
  getch(); // Wait for key press

  // Cleanup
  endwin();
  return EXIT_SUCCESS;
}

// Map brightness to ASCII characters
char brightnessToChar(unsigned char brightness) {
    const std::string chars = "@%#*+=-:. "; // Dark to light
    int index = (brightness * (chars.size() - 1)) / 255;
    return chars[index];
}