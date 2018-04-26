import qualified Data.List as List
import qualified Data.Map as Map
import qualified Data.Set as Set
lucky :: (Integral a) => a -> String   
lucky 7 = "LUCKY NUMBER SEVEN!"   
lucky x = "Sorry, you're out of luck, pal!"   

test :: (Integral a) => a->String
test 1="1"
test 2="2"
test x="233"

head' :: [a] -> a   
head' [] = error "Can't call head on an empty list, dummy!"   
head' (x:_) = x

bmiTell :: (RealFloat a) => a -> a -> String   
bmiTell weight height   
    | weight / height ^ 2 <= 18.5 = "You're underweight, you emo, you!"   
    | weight / height ^ 2 <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"   
    | weight / height ^ 2 <= 30.0 = "You're fat! Lose some weight, fatty!"   
    | otherwise                 = "You're a whale, congratulations!"

head2 :: [a]->a
head2 xs=case xs of []->error "empty list!"
                    (x:_)->x
describe :: [a]->String
describe string="233 "++case string of []->"empty"
                                       [x]->"one"
                                       (x:_)->"long"

reverse' :: [a] -> [a]   
reverse' [] = []   
reverse' (x:xs) = reverse' xs ++ [x]

applytwice :: (a->a)->a->a
applytwice f x=f (f x)


zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]   
zipWith' _ [] _ = []   
zipWith' _ _ [] = []   
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys

sum' :: (Num a)=>[a]->a
sum' xs=foldl (\acc x->acc+x) 0 xs


map' :: (a->b)->[a]->[b]
map' f xs=foldr (\x acc->f x:acc) [] xs

data Person = Person { firstName :: String   
                     , lastName :: String   
                     , age :: Int   
                     , height :: Float   
                     , phoneNumber :: String   
                     , flavor :: String   
                     } deriving (Show)