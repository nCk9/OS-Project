class CreateJobs < ActiveRecord::Migration[6.0]
  def change
    create_table :jobs do |t|
      t.integer :num
      t.integer :wt

      t.timestamps
    end
  end
end
