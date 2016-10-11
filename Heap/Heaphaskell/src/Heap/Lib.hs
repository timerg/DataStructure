module Heap.Lib where

data Eitherer a b = Lefter a | Righter b deriving (Read, Show)
data Node = Leaf Int | Node Int deriving (Show)
instance Eq Node where
    Leaf a == Leaf b = a == b
    Node a == Node b = a == b
    Node a == Leaf b = a == b
    Leaf a == Node b = a == b

instance Ord Node where
    compare (Leaf a) (Leaf b) = compare a b
    compare (Node a) (Node b) = compare a b
    compare (Node a) (Leaf b) = compare a b

(!.!) :: [a] -> Int -> Eitherer String a
(!.!) (s:xs) 1 = Righter s
(!.!) [] i = Lefter "index overflow"
(!.!) (s:xs) i = xs !.! (i - 1)


val :: Node -> Int
val (Leaf a) = a
val (Node a) = a
-- val (Node_single a) = a
-- val (Root a) = a

node :: Int -> Node
node a = Node a

-- node_single :: Int -> Node
-- node_single a = Node_single a

leaf :: Int -> Node
leaf a = Leaf a


typify :: [Int] -> [Node]
typify xs = reunion $ nodefy $ splitAt (parent (length xs)) xs
                    where layer = floor $ logBase 2 (fromIntegral (length xs):: Double)
                          nodefy (a, b) =  (map node a , map leaf b)
                          reunion (a , b) = a ++ b

parent :: Int -> Int
parent a = floor $ (fromIntegral a :: Double) / 2

sibling :: Int -> Int
sibling a = case even a of
        True -> a + 1
        False -> a - 1


switch :: Int -> Int -> [Node] -> [Node]
switch i1 i2 xs = if i1 > length xs || i2 > length xs then error "index wrong"
                  else replace (replace xs s2 i1) s1 i2
                                    where s1 = case xs !.! i1 of
                                                Righter a -> a
                                                Lefter b -> error ("[SWITCH]:s1:index overgflow" ++ b)
                                          s2 = case xs !.! i2 of
                                                Righter a -> a
                                                Lefter b -> error ("[SWITCH]:s1:index overgflow" ++ b)

replace :: [Node] -> Node -> Int -> [Node]
replace (s:xs) a i = if i /= 1 then (s:(replace xs a (i - 1)))
                    else case s of
                        Leaf x -> (leaf $ val a):xs
                        Node x -> (node $ val a):xs

heapify :: [Node] -> Int -> [Node]
heapify xs i = let fstchild = xs !.! (i * 2)
                   sndchild = xs !.! (i * 2 + 1)
                   l = length xs
               in if i == 0
                   then
                       xs
                   else
                       case xs !.! i of
                           Lefter b -> error "[HEAPIFY]: index overflow"
                           Righter (Leaf a) -> heapify xs (parent i)
                           Righter (Node a)
                               -> case maxFamily (Righter (Node a)) fstchild sndchild of
                                   One -> heapify xs (parent i)
                                   Two -> heapify (switch i (i * 2) xs) (i * 2)
                                   Three -> heapify (switch i (i * 2 + 1) xs) (i * 2 + 1)

instance (Eq a, Eq b) => Eq (Eitherer a b) where
    Righter a == Righter b = a == b
    Lefter a == Lefter b = False

instance (Ord a, Ord b) => Ord (Eitherer a b) where
    compare (Righter a) (Righter c) = compare a c
    compare (Righter a) (Lefter b) = GT
    compare (Lefter a) (Righter b) = LT


data Three = One | Two | Three


maxFamily :: (Ord a) => Eitherer a Node -> Eitherer a Node -> Eitherer a Node -> Three
maxFamily a b c =  let max' = maximum [a, b, c] in
                    if max' == a
                        then One
                    else if max' == b
                        then Two
                    else  Three


heapSort xs = heapSort' l $ heapify (typify xs) l
                    where l = length xs
--
heapSort' :: Int -> [Node] -> [Int]
heapSort' 1 (s:[]) = (val s):[]
heapSort' i (s:xs) = (heapSort' (i - 1) $ heapify (init $ switch 1 i (s:xs)) 1) ++ [val s]

-- init' :: [Node] -> [Node]
-- init' xs =










--