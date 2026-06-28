-- Forward migration: N-dependency input operations.
-- Converts input_operation_order/input_deadline to TEXT (comma-separated lists)
-- and drops the now-unused alternative_* columns.
BEGIN;

-- Safety backup; drop after a successful verified run.
CREATE TABLE IF NOT EXISTS static_initial_data_control_operations_backup_20260628 AS
    SELECT * FROM static_initial_data_control_operations;

ALTER TABLE static_initial_data_control_operations
    ALTER COLUMN input_operation_order TYPE text USING input_operation_order::text,
    ALTER COLUMN input_deadline        TYPE text USING input_deadline::text;

ALTER TABLE static_initial_data_control_operations
    DROP COLUMN IF EXISTS alternative_operation_order,
    DROP COLUMN IF EXISTS alternative_deadline;

COMMIT;
