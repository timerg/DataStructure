-- A pratice of constructing Queue with resources from:
    -- https://www.well-typed.com/blog/2016/01/efficient-queues/
module Queue where


data StrictList a = SNil | SCons a !(StrictList a)

-- | Append two strict lists
app :: StrictList a -> StrictList a -> StrictList a
app SNil ys         = ys
app (SCons x xs) ys = SCons x (app xs ys)

-- | Reverse a strict list
rev :: StrictList a -> StrictList a
rev = go SNil
  where
    go :: StrictList a -> StrictList a -> StrictList a
    go acc SNil         = acc
    go acc (SCons x xs) = go (SCons x acc) xs

data Queue1 a = Q1 !Int !(StrictList a) !Int !(StrictList a)

instance Queue Queue1 where
  empty                           = Q1 0 SNil 0 SNil
  head (Q1 _ (SCons x _ ) _ _ )   = x
  tail (Q1 f (SCons _ xs) r ys)   = inv1 $ Q1 (f-1) xs r ys
  snoc (Q1 f xs           r ys) y = inv1 $ Q1 f xs (r+1) (SCons y ys)

-- This Rule should be followed:
-- Queue Invariant: The front of the queue cannot be shorter than the rear.
-- If wrong thing happened such as:
-- abc gfed
    -- then:  =>  abc defg => abcdefg _
-- This is implemented by the func below:
inv1 :: Queue1 a -> Queue1 a
inv1 q@(Q1 f xs r ys)
  | f < r     = Q1 (f+r) (xs `app` rev ys) 0 SNil
  | otherwise = q

someFunc :: IO ()
someFunc = putStrLn "someFunc"






