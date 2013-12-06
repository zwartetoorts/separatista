On Error Resume Next

Set doc = CreateObject("Separatista.MT940SDocument")
    
If doc.Open("C:\Users\Okkel\Downloads\MT940.swi") = 0 Then
	WScript.Echo "Number of documents:" & doc.RecordsetCount

	For Each rs In doc
		WScript.Echo "** New Recordset"
		WScript.Echo "CurrencyClient: " & rs.CurrencyClient
		WScript.Echo "Transaction reference: " & rs.TransactionReference
		WScript.Echo "Serial Number: " & rs.SerialNumber
		WScript.Echo "Client IBAN: " & rs.IBANClient.IBAN
		WScript.Echo "Previous Balance: " & CCur(rs.PreviousBalance)
		WScript.Echo "Previous Balance Date:  " & FormatDateTime(rs.PreviousBalanceDate, 1)
		WScript.Echo "Current Balance: " & CCur(rs.CurrentBalance)
		WScript.Echo "Current Balance Date:  " & FormatDateTime(rs.CurrenctBalanceDate, 1)
    Next
Else
    WScript.Echo "Parser error"
End If
  
if Err.Number <> 0 then
	WScript.Echo Err.Description
End if

Do While Not WScript.StdIn.AtEndOfLine
   Input = WScript.StdIn.Read(1)
Loop
WScript.Echo "The script is complete." 