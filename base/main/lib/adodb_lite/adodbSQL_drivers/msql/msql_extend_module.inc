<?php
/**
 * ADOdb Lite Extend Module for Mysqlt
 * 
 */

eval('class msql_extend_EXTENDER extends msql_'. $last_module . '_ADOConnection { }');

class msql_extend_ADOConnection extends msql_extend_EXTENDER
{
	function &GetAssoc($sql, $inputarr=false, $force_array = false, $first2cols = false)
	{
		$data = false;
		$result =& $this->Execute($sql, $inputarr);
		if ($result) {
			$data =& $result->GetAssoc($force_array, $first2cols);
			$result->Close();
		}
		return $data;
	}

	/**
	 * Generates a sequence id and stores it in $this->genID;
	 * GenID is only available if $this->hasGenID = true;
	 *
	 * @param seqname		name of sequence to use
	 * @param startID		if sequence does not exist, start at this ID
	 * @return		0 if not supported, otherwise a sequence id
	 */
	var $genID = 0;

	function GenID($seqname='adodbseq', $startID=1)
	{
		return 0;
	}

}

eval('class msql_extend_resultset_EXTENDER extends msql_'. $last_module . '_ResultSet { }');

class msql_extend_ResultSet extends msql_extend_resultset_EXTENDER
{
	function &GetAssoc($force_array = false, $first2cols = false) 
	{
		$results = false;
		
		if ($this->_numOfFields > 1) {
			$numIndex = isset($this->fields[0]);
			$results = array();
			if (!$first2cols && ($this->_numOfFields > 2 || $force_array)) {
				if ($numIndex) {
					while (!$this->EOF) {
						$results[trim($this->fields[0])] = array_slice($this->fields, 1);
						$this->MoveNext();
					}
				} else {
					while (!$this->EOF) {
						$results[trim(reset($this->fields))] = array_slice($this->fields, 1);
						$this->MoveNext();
					}
				}
			} else {
				if ($numIndex) {
					while (!$this->EOF) {
						$results[trim(($this->fields[0]))] = $this->fields[1];
						$this->MoveNext();
					}
				} else {
					while (!$this->EOF) {
						$v1 = trim(reset($this->fields));
						$v2 = ''.next($this->fields); 
						$results[$v1] = $v2;
						$this->MoveNext();
					}
				}
			}
		}
		return $results; 
	}

}
?>