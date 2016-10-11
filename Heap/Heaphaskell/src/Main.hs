{-# LANGUAGE OverloadedStrings #-}
module Main where

import Prelude hiding (readFile)
import Heap.Lib
import Data.ByteString.Char8 (ByteString, readFile)
import Data.Attoparsec.ByteString.Char8





main :: IO ()
main = do
    print $ heapSort testArray
    return ()

testArray :: [Int]
testArray = [16, 8, 10, 14, 7, 9, 3, 2, 4, 1]

testArray_t = [Node 16,Node 8,Node 10,Node 14,Node 7,Leaf 9,Leaf 3,Leaf 2,Leaf 4, Leaf 1]
testArray_h = heapify (typify testArray) 10