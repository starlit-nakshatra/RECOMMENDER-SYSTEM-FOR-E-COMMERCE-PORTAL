			<form action="find.php" method="post">
				<fieldset>
					<div class="form-group">
						<select autofocus required name="product">
							<option value="">--Select Product Type--</option>
							<option value="phone">Smart Phone</option>
							<option value="tv">Smart-T.V.</option>
						</select>
					</div>
					<div class="form-group">
						<input required autofocus class="form-control" name="mini" placeholder="Minimum Price" type="text"/>
					</div>
					<div class="form-group">
						<input required autofocus class="form-control" name="maxi" placeholder="Maximum Price" type="text"/>
					</div>
					<div class="form-group">
						<button type="submit" class="btn btn-default">Search</button>
					</div>
				</fieldset>
				</form>
				<hr>