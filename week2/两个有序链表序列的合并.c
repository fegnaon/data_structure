List Merge( List L1, List L2 )
{
    List L = (struct Node*)malloc(sizeof(struct Node));
    PtrToNode pt1 = L1->Next,pt2 = L2->Next,pt = L;
    while (pt1 && pt2)
    {
        if (pt1->Data > pt2->Data){
            pt->Next = pt2;
            pt2 = pt2->Next;
            pt = pt->Next;
        }
        else{
            pt->Next = pt1;
            pt1 = pt1->Next;
            pt = pt->Next;
        }
    }
    if (pt2){
        for (; pt2->Next;pt->Next = pt2,pt2 = pt2->Next,pt = pt->Next);
        pt->Next = pt2;
        pt = pt->Next;
    }
    if (pt1){
        for (; pt1->Next;pt->Next = pt1,pt1 = pt1->Next,pt = pt->Next);
        pt->Next = pt1;
        pt = pt->Next;
    }
    pt->Next = NULL;
    L1->Next = NULL;
    L2->Next = NULL;

    return L;
}