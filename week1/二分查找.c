Position BinarySearch( List L, ElementType X )
{
    Position posl = 0,posr = L->Last,pos;
    ElementType i;
    while (1)
    {
        pos = (posl + posr) / 2;
        i = L->Data[pos];
        if (pos == posl || pos == posr){
            if (L->Data[posl] == X){
                return posl;
            }
            else if (L->Data[posr] == X){
                return posr;
            }
            else{
                return NotFound;
            }
        }
        if (i == X){
            return pos;
        }
        else if (i > X){
            posr = pos;
        }
        else{
            posl = pos;
        }
    }
}