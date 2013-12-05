    Set doc = CreateObject("Separatista.MT940SDocument")
    
    If doc.Open("C:\Users\Okkel\Downloads\MT940.swi") = OK Then
		Print "***Debug output***"
        For Each rs In doc
            MsgBox rs.Currency
            
        Next
    Else
        MsgBox "Parser error"
    End If
    
