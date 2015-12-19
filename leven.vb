Public Function valuePhrase#(ByRef S1$, ByRef S2$)
    valuePhrase = LevenshteinDistance(S1, S2)
End Function

Public Function valueWords#(ByRef S1$, ByRef S2$)
    Dim wordsS1$(), wordsS2$()
    wordsS1 = SplitMultiDelims(S1, " _-")
    wordsS2 = SplitMultiDelims(S2, " _-")
    Dim word1%, word2%, thisD#, wordbest#
    Dim wordsTotal#
    For word1 = LBound(wordsS1) To UBound(wordsS1)
        wordbest = Len(S2)
        For word2 = LBound(wordsS2) To UBound(wordsS2)
            thisD = LevenshteinDistance(wordsS1(word1), wordsS2(word2))
            If thisD < wordbest Then wordbest = thisD
            If thisD = 0 Then GoTo foundbest
        Next word2
foundbest:
        wordsTotal = wordsTotal + wordbest
    Next word1
    valueWords = wordsTotal
End Function


Function SplitMultiDelims(ByRef Text As String, ByRef DelimChars As String, _
        Optional ByVal IgnoreConsecutiveDelimiters As Boolean = False, _
        Optional ByVal Limit As Long = -1) As String()
    Dim ElemStart As Long, N As Long, M As Long, Elements As Long
    Dim lDelims As Long, lText As Long
    Dim Arr() As String

    lText = Len(Text)
    lDelims = Len(DelimChars)
    If lDelims = 0 Or lText = 0 Or Limit = 1 Then
        ReDim Arr(0 To 0)
        Arr(0) = Text
        SplitMultiDelims = Arr
        Exit Function
    End If
    ReDim Arr(0 To IIf(Limit = -1, lText - 1, Limit))

    Elements = 0: ElemStart = 1
    For N = 1 To lText
        If InStr(DelimChars, Mid(Text, N, 1)) Then
            Arr(Elements) = Mid(Text, ElemStart, N - ElemStart)
            If IgnoreConsecutiveDelimiters Then
                If Len(Arr(Elements)) > 0 Then Elements = Elements + 1
            Else
                Elements = Elements + 1
            End If
            ElemStart = N + 1
            If Elements + 1 = Limit Then Exit For
        End If
    Next N

    If ElemStart <= lText Then Arr(Elements) = Mid(Text, ElemStart)

    If IgnoreConsecutiveDelimiters Then If Len(Arr(Elements)) = 0 Then Elements = Elements - 1

    ReDim Preserve Arr(0 To Elements) 
    SplitMultiDelims = Arr
End Function